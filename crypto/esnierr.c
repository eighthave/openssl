/*
 * Generated by util/mkerr.pl DO NOT EDIT
 * Copyright 1995-2019 The OpenSSL Project Authors. All Rights Reserved.
 *
 * Licensed under the Apache License 2.0 (the "License").  You may not use
 * this file except in compliance with the License.  You can obtain a copy
 * in the file LICENSE in the source distribution or at
 * https://www.openssl.org/source/license.html
 */

#include <openssl/err.h>
#include <openssl/esnierr.h>

#ifndef OPENSSL_NO_ERR

static const ERR_STRING_DATA ESNI_str_functs[] = {
    {ERR_PACK(ERR_LIB_ESNI, ESNI_F_BASE64_DECODE, 0), "esni_base64_decode"},
    {ERR_PACK(ERR_LIB_ESNI, ESNI_F_CHECKSUM_CHECK, 0), "esni_checksum_check"},
    {ERR_PACK(ERR_LIB_ESNI, ESNI_F_DEC, 0), "ESNI_dec"},
    {ERR_PACK(ERR_LIB_ESNI, ESNI_F_ENC, 0), "ESNI_enc"},
    {ERR_PACK(ERR_LIB_ESNI, ESNI_F_ESNI_AEAD_DEC, 0), "esni_aead_dec"},
    {ERR_PACK(ERR_LIB_ESNI, ESNI_F_ESNI_AEAD_ENC, 0), "esni_aead_enc"},
    {ERR_PACK(ERR_LIB_ESNI, ESNI_F_ESNI_BASE64_DECODE, 0),
     "esni_base64_decode"},
    {ERR_PACK(ERR_LIB_ESNI, ESNI_F_ESNI_CHECKSUM_CHECK, 0),
     "esni_checksum_check"},
    {ERR_PACK(ERR_LIB_ESNI, ESNI_F_ESNI_MAKE_RD, 0), "esni_make_rd"},
    {ERR_PACK(ERR_LIB_ESNI, ESNI_F_ESNI_MAKE_SE_FROM_ER, 0),
     "esni_make_se_from_er"},
    {ERR_PACK(ERR_LIB_ESNI, ESNI_F_KEY_DERIVATION, 0), "key_derivation"},
    {ERR_PACK(ERR_LIB_ESNI, ESNI_F_MAKEESNICONTENTHASH, 0),
     "makeesnicontenthash"},
    {ERR_PACK(ERR_LIB_ESNI, ESNI_F_NEW_FROM_BASE64, 0),
     "SSL_ESNI_RECORD_new_from_binary"},
    {ERR_PACK(ERR_LIB_ESNI, ESNI_F_SERVER_ENABLE, 0), "SSL_esni_server_enable"},
    {ERR_PACK(ERR_LIB_ESNI, ESNI_F_SSL_ESNI_DEC, 0), "SSL_ESNI_dec"},
    {ERR_PACK(ERR_LIB_ESNI, ESNI_F_SSL_ESNI_DUP, 0), "SSL_ESNI_dup"},
    {ERR_PACK(ERR_LIB_ESNI, ESNI_F_SSL_ESNI_ENC, 0), "SSL_ESNI_enc"},
    {ERR_PACK(ERR_LIB_ESNI, ESNI_F_SSL_ESNI_NEW_FROM_BASE64, 0),
     "SSL_ESNI_new_from_base64"},
    {ERR_PACK(ERR_LIB_ESNI, ESNI_F_SSL_ESNI_RECORD_NEW_FROM_BINARY, 0),
     "SSL_ESNI_RECORD_new_from_binary"},
    {ERR_PACK(ERR_LIB_ESNI, ESNI_F_SSL_ESNI_SERVER_ENABLE, 0),
     "SSL_esni_server_enable"},
    {ERR_PACK(ERR_LIB_ESNI, ESNI_F_SSL_ESNI_WRAP_KEYSHARE, 0),
     "SSL_ESNI_wrap_keyshare"},
    {0, NULL}
};

static const ERR_STRING_DATA ESNI_str_reasons[] = {
    {ERR_PACK(ERR_LIB_ESNI, 0, ESNI_R_BASE64_DECODE_ERROR),
    "base64 decode error"},
    {ERR_PACK(ERR_LIB_ESNI, 0, ESNI_R_NOT_IMPL), "not implemented"},
    {ERR_PACK(ERR_LIB_ESNI, 0, ESNI_R_RR_DECODE_ERROR),
    "can't decode DNS resource record"},
    {0, NULL}
};

#endif

int ERR_load_ESNI_strings(void)
{
#ifndef OPENSSL_NO_ERR
    if (ERR_func_error_string(ESNI_str_functs[0].error) == NULL) {
        ERR_load_strings_const(ESNI_str_functs);
        ERR_load_strings_const(ESNI_str_reasons);
    }
#endif
    return 1;
}
