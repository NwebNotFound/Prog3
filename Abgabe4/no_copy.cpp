#include "channel.hpp"

int main() {
    Channel c = channel(4);
#ifdef COPY_SENDER
    Sender tx2 = c.tx;
#endif
#ifdef COPY_RECEIVER
    Receiver rx2 = c.rx;
#endif
}
