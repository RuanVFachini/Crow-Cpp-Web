#pragma once

#include <jwt-cpp/jwt.h>

#include "../types/app_types.h"

#define JWT_TYPE "JWT"
#define JWT_ISSUER "my-app-issuer"
#define JWT_SECRET "a83c513180b98b28d68e45eec62c5343e08cd0b8d59041a4b2bd1e52c376161f"

namespace JwtHelper {

std::string createToken(User& user) {
    return jwt::create()
        .set_issuer(JWT_ISSUER)
        .set_type(JWT_TYPE)
        .set_issued_now()
        .set_expires_in(std::chrono::seconds{36000})
        .set_payload_claim("email", jwt::claim(user.email))
        .sign(jwt::algorithm::hs256(JWT_SECRET));
}

}  // namespace JwtHelper
