#include "channel.hpp"

void by_value(Sender tx) { tx.send(1); }
void by_rref(Sender&& tx) { tx.send(2); }
void by_rref_take(Sender&& tx) {
    Sender owned = std::move(tx);
    owned.send(3);
}

int main() {
    Channel a = channel(8);
    Channel b = channel(8);

    std::cout << "by_value(std::move(b.tx)):\n";
    by_value(std::move(b.tx));

    std::cout << "by_rref(std::move(a.tx)):\n";
    by_rref(std::move(a.tx));
    a.tx.send(4);
    std::cout << "a.tx is still usable\n";

    std::cout << "by_rref_take(std::move(a.tx)):\n";
    by_rref_take(std::move(a.tx));

    std::cout << "move assignment:\n";
    Sender s = std::move(b.tx);
    s = Sender{std::make_shared<SpscQueue>(1)};

    int r1 = a.rx.recv();
    int r2 = a.rx.recv();
    int r3 = a.rx.recv();
    int r4 = b.rx.recv();
    std::cout << "received: " << r1 << ' ' << r2 << ' ' << r3 << ' ' << r4 << '\n';
}
