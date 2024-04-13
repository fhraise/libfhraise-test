#include <iostream>

#include "libfhraisepy_api.h"
#include "throwable.h"

auto lib = libfhraisepy_symbols();
auto root = lib->kotlin.root.xyz.xfqlittlefan.fhraise.py;

auto logger = root.Logger.Logger("libfhraise_test");

auto get_result() {
    auto [pinned] = root.Message.Register.Result.Success._instance();
    return pinned;
}

int main() {
    const auto client = root.Client.Client("localhost", 11451);

    Throwable *throwable_ptr;

    root.Logger.debug(logger, "Connecting to the server.");

    if (const auto connection_result = root.Client.connect(client, &throwable_ptr); !connection_result) {
        auto [type, ref, message, stacktrace, stacktraceSize] = *throwable_ptr;

        root.Logger.error(logger, "Error connecting to the server.");
        root.Logger.error(logger, ("Error type: " + std::string(type)).c_str());
        root.Logger.error(logger, ("Error message: " + std::string(message)).c_str());
        for (int i = 0; i < stacktraceSize; ++i) {
            root.Logger.error(logger, stacktrace[i]);
        }

        return 1;
    }

    root.Logger.debug(logger, "Receiving data from the server.");

    while (true) {
        char *message_type;
        libfhraisepy_KNativePtr ref;

        if (const auto receive = root.Client.receive(client, &message_type, &ref, &throwable_ptr,
                                                     reinterpret_cast<void *>(get_result));
            !receive) {
            auto [type, ref, message, stacktrace, stacktraceSize] = *throwable_ptr;

            root.Logger.error(logger, "Error receiving data from the server.");
            root.Logger.error(logger, ("Error type: " + std::string(type)).c_str());
            root.Logger.error(logger, ("Error message: " + std::string(message)).c_str());
            for (int i = 0; i < stacktraceSize; ++i) {
                root.Logger.error(logger, stacktrace[i]);
            }

            return 1;
        }

        std::string message_type_string(message_type);

        root.Logger.debug(logger, ("Received message type: " + message_type_string).c_str());

        if (message_type_string == "xyz.xfqlittlefan.fhraise.py.Message.Register.Frame") {
            const auto ref_frame = new libfhraisepy_kref_xyz_xfqlittlefan_fhraise_py_Message_Register_Frame(ref);
            const auto call_id = root.Message.Register.Frame.get_callId(*ref_frame);
            auto content = root.Message.Register.Frame.get_content(*ref_frame);

            root.Logger.debug(logger, ("Received call ID: " + std::string(call_id)).c_str());

            delete &ref_frame;
        }
    }
}
