#include "channel.hpp"
#include <thread>

void producer_fun(Sender tx, int N) {
    for (int i = 1; i <= N; ++i) {
        tx.send(i);
    }
}

int main() {
    Channel c = channel(2);

    constexpr int N = 8;

    std::thread producer([&] { producer_fun(std::move(c.tx), N); });

    for (int i = 0; i < N; ++i) {
        int x = c.rx.recv();
        std::cout << "received = " << x << '\n';
    }

    //c.tx.send(1);
    //Receiver rx2 = c.rx;

    producer.join();
}
