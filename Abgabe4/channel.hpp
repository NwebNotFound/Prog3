#pragma once
#include <atomic>
#include <cassert>
#include <cstddef>
#include <iostream>
#include <memory>
#include <vector>

class SpscQueue {
    std::vector<int>         buf_;
    const std::size_t        cap_;
    std::atomic<std::size_t> head_{0};
    std::atomic<std::size_t> tail_{0};

public:
    SpscQueue(std::size_t capacity)
        : buf_(capacity + 1),
          cap_(capacity + 1) {}

    bool try_push(const int& v) {
        const auto t = tail_.load(std::memory_order_relaxed);
        if ((t + 1) % cap_ == head_.load(std::memory_order_acquire))
            return false;
        buf_[t] = v;
        tail_.store((t + 1) % cap_, std::memory_order_release);
        return true;
    }

    bool try_pop(int& out) {
        const auto h = head_.load(std::memory_order_relaxed);
        if (h == tail_.load(std::memory_order_acquire))
            return false;
        out = std::move(buf_[h]);
        head_.store((h + 1) % cap_, std::memory_order_release);
        return true;
    }

    void push_wait(const int& v) { while (!try_push(v)); }
    int  pop_wait()              { int v; while (!try_pop(v)); return v; }
};

// shared_ptr: Sender und Receiver teilen sich dieselbe Queue, der zuletzt
// zerstörte Teil gibt sie frei. unique_ptr erlaubt nur einen Besitzer.
// Nur der Zeiger wird verschoben, die Queue selbst nie.
class Sender {
    std::shared_ptr<SpscQueue> q_;

public:
    explicit Sender(std::shared_ptr<SpscQueue> q) : q_(std::move(q)) {}

    Sender(const Sender&)            = delete;
    Sender& operator=(const Sender&) = delete;

    Sender(Sender&& other) noexcept : q_(std::move(other.q_)) {
        std::cout << "Sender move ctor\n";
    }

    Sender& operator=(Sender&& other) noexcept {
        std::cout << "Sender move assign\n";
        q_ = std::move(other.q_);
        return *this;
    }

    void send(const int& v) {
        assert(q_ && "send() called on moved-from Sender");
        q_->push_wait(v);
    }
};

class Receiver {
    std::shared_ptr<SpscQueue> q_;

public:
    explicit Receiver(std::shared_ptr<SpscQueue> q) : q_(std::move(q)) {}

    Receiver(const Receiver&)            = delete;
    Receiver& operator=(const Receiver&) = delete;

    Receiver(Receiver&&) noexcept            = default;
    Receiver& operator=(Receiver&&) noexcept = default;

    int recv() {
        assert(q_ && "recv() called on moved-from Receiver");
        return q_->pop_wait();
    }
};

struct Channel {
    Sender   tx;
    Receiver rx;
};

inline Channel channel(std::size_t capacity) {
    auto q = std::make_shared<SpscQueue>(capacity);
    return Channel{Sender{q}, Receiver{std::move(q)}};
}
