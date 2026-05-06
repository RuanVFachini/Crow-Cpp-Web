#pragma once

#include <jwt-cpp/jwt.h>

#include "../types/app_types.h"

#define JWT_TYPE "JWT"
#define JWT_ISSUER "my-app-issuer"
#define JWT_SECRET "a83c513180b98b28d68e45eec62c5343e08cd0b8d59041a4b2bd1e52c376161f"
#define SCHEMA "Bearer "

namespace JwtHelper {

std::string createToken(User& user) {
    return jwt::create()
        .set_issuer(JWT_ISSUER)
        .set_type(JWT_TYPE)
        .set_issued_now()
        .set_expires_in(std::chrono::seconds{36000})
        .set_payload_claim("id", jwt::claim(std::to_string(user.id)))
        .set_payload_claim("name", jwt::claim(user.name))
        .set_payload_claim("email", jwt::claim(user.email))
        .sign(jwt::algorithm::hs256(JWT_SECRET));
}

AuthResult decodeToken(const std::string& token) {
    try {
        auto decoded = jwt::decode(token);

        auto verifier = jwt::verify()
                            .allow_algorithm(jwt::algorithm::hs256(JWT_SECRET))
                            .with_issuer(JWT_ISSUER);

        verifier.verify(decoded);

        Principal p;
        p.id = std::stoi(decoded.get_payload_claim("id").as_string());
        p.name = decoded.get_payload_claim("name").as_string();
        p.email = decoded.get_payload_claim("email").as_string();

        return AuthResult{p, true};

    } catch (const std::exception& e) {
        return AuthResult{Principal{}, false};
    }
}

}  // namespace JwtHelper
