#include <iostream>
#include "libfhraise_api.h"

auto lib = libfhraise_symbols();
auto root = lib->kotlin.root;

libfhraise_kref_Result get_register_result() {
    auto success = root.Result.RegisterResult.Success._instance();
    auto result = new libfhraise_kref_Result(success.pinned);
    return *result;
}

int main() {
    auto client = root.Client.Client("localhost", 8080);

    char **actions;
    int actions_size;

    root.Client.getActionEntries(client, &actions, &actions_size);

    for (int i = 0; i < actions_size; ++i) {
        std::cout << "Action[" << i << "]: " << actions[i] << std::endl;
    }

    char *exception_type;
    char *exception_message;
    char **exception_stacktrace;
    int exception_stacktrace_size;

    auto connect_result = root.Client.connect(client, &exception_type, &exception_message, &exception_stacktrace,
                                              &exception_stacktrace_size);

    if (!connect_result) {
        std::cout << "Failed to connect to the server:" << std::endl;
        std::cout << "Exception type: " << exception_type << std::endl;
        std::cout << "Exception message: " << exception_message << std::endl;
        for (int i = 0; i < exception_stacktrace_size; ++i) {
            std::cout << "Exception stacktrace[" << i << "]: " << exception_stacktrace[i] << std::endl;
        }
        return 1;
    }

    unsigned char action;
    unsigned char *data;
    int data_size;

    root.Client.receive(client, &action, &data, &data_size, (void *) get_register_result);

    for (int i = 0; i < data_size; ++i) {
        std::cout << "Data[" << i << "]: " << static_cast<int>(data[i]) << " " << data[i] << std::endl;
    }

    return 0;
}
