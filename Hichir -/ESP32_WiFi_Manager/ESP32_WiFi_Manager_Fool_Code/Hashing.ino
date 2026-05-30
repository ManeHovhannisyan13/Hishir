String sha256(String input) {
    byte shaResult[32];
    mbedtls_sha256_context ctx;

    mbedtls_sha256_init(&ctx);
    mbedtls_sha256_starts(&ctx, 0);

    mbedtls_sha256_update(
        &ctx,
        (const unsigned char*)input.c_str(),
        input.length()
    );

    mbedtls_sha256_finish(&ctx, shaResult);
    mbedtls_sha256_free(&ctx);

    String hash = "";

    for (int i = 0; i < 32; i++) {
        char str[3];
        sprintf(str, "%02x", shaResult[i]);
        hash += str;
    }

    return hash;
}
