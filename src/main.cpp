#include <fmt/core.h>
#include <restinio/core.hpp>
#include <string_view>
#include <cstdlib>

#include "runit.h"

using namespace restinio;

template<typename T>
struct fmt::formatter<std::optional<T>> : fmt::formatter<T>
{
    auto format(const std::optional<T>& v, format_context& ctx) const
    {
        if (v) {
            fmt::formatter<T>::format(*v, ctx);
            return ctx.out();
        }
        return fmt::format_to(ctx.out(), "null");
    }
};

int main() {
    // Create express router for our service.
    auto router = std::make_unique<router::express_router_t<>>();
    router->http_post(
        R"(/bitbox/portforward/:port(\d+))",
        [](auto req, auto params) {
            int port = cast_to<int>(params["port"]);
            auto rem_out = exec("incus config device remove bitbox portforward");
            auto add_out = exec(fmt::format("incus config device add bitbox portforward proxy listen=tcp:0.0.0.0:{0} connect=tcp:127.0.0.1:{0}", port));
            auto device_out = exec("incus config device show bitbox");
            return req->create_response()
                    .set_body(fmt::format("{}\n{}\n{}\n", rem_out, add_out, device_out))
                    .done();
        }
    );

    router->non_matched_request_handler(
            [](auto req){
                return req->create_response(restinio::status_not_found()).connection_close().done();
            });

    // Launching a server with custom traits.
    struct my_server_traits : public default_single_thread_traits_t {
        using request_handler_t = restinio::router::express_router_t<>;
    };

    restinio::run(
            restinio::on_this_thread<my_server_traits>()
                    .address("127.0.0.1")
                    .port(7680)
                    .request_handler(std::move(router)));

    return 0;
}