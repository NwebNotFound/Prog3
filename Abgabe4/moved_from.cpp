#include "channel.hpp"

int main() {
    Channel c = channel(4);
    Sender other = std::move(c.tx);
    c.tx.send(1);
}
