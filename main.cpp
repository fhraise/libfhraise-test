#include <iostream>
#include "libfhraise_api.h"

int main() {
    auto lib = libfhraise_symbols();
    auto root = lib->kotlin.root;
    auto client = root.Client.Client("localhost", 8080);

    auto actions = root.Client.getActionEntries(client);

    std::cout << "Actions: " << actions << std::endl;
    lib->DisposeString(actions);

    unsigned char action;
    unsigned char *data;
    int size;

    root.Client.receive(client, &action, &data, &size);

    for (int i = 0; i < size; ++i) {
        std::cout << "Data[" << i << "]: " << static_cast<int>(data[i]) << " " << data[i] << std::endl;
    }

    return 0;
}
