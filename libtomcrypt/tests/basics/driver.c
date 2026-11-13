#include <string.h>

#include <tomcrypt.h>

#undef NDEBUG
#include <assert.h>

int main ()
{
  /* Hash the FIPS 180-2 test message through the hash descriptor table.
   */
  {
    static const unsigned char e[32] = {
      0xba, 0x78, 0x16, 0xbf, 0x8f, 0x01, 0xcf, 0xea,
      0x41, 0x41, 0x40, 0xde, 0x5d, 0xae, 0x22, 0x23,
      0xb0, 0x03, 0x61, 0xa3, 0x96, 0x17, 0x7a, 0x9c,
      0xb4, 0x10, 0xff, 0x61, 0xf2, 0x00, 0x15, 0xad};

    unsigned char h[32];
    unsigned long n = sizeof (h);
    int i;

    assert (register_hash (&sha256_desc) != -1);
    assert ((i = find_hash ("sha256")) != -1);

    assert (hash_memory (i, (const unsigned char*) "abc", 3, h, &n) ==
            CRYPT_OK);
    assert (n == sizeof (e) && memcmp (h, e, n) == 0);
  }

  /* Encrypt the FIPS 197 AES-128 test block with both the full and the
   * encrypt-only AES implementations.
   */
  {
    static const unsigned char k[16] = {
      0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07,
      0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f};

    static const unsigned char p[16] = {
      0x00, 0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77,
      0x88, 0x99, 0xaa, 0xbb, 0xcc, 0xdd, 0xee, 0xff};

    static const unsigned char e[16] = {
      0x69, 0xc4, 0xe0, 0xd8, 0x6a, 0x7b, 0x04, 0x30,
      0xd8, 0xcd, 0xb7, 0x80, 0x70, 0xb4, 0xc5, 0x5a};

    unsigned char c[16], d[16];
    symmetric_ECB ecb;
    symmetric_key sk;
    int i;

    assert (register_cipher (&aes_desc) != -1);
    assert ((i = find_cipher ("aes")) != -1);

    assert (ecb_start (i, k, sizeof (k), 0, &ecb) == CRYPT_OK);
    assert (ecb_encrypt (p, c, sizeof (p), &ecb) == CRYPT_OK);
    assert (memcmp (c, e, sizeof (e)) == 0);
    assert (ecb_decrypt (c, d, sizeof (c), &ecb) == CRYPT_OK);
    assert (memcmp (d, p, sizeof (p)) == 0);
    assert (ecb_done (&ecb) == CRYPT_OK);

    memset (c, 0, sizeof (c));

    assert (aes_enc_desc.setup (k, sizeof (k), 0, &sk) == CRYPT_OK);
    assert (aes_enc_desc.ecb_encrypt (p, c, &sk) == CRYPT_OK);
    assert (memcmp (c, e, sizeof (e)) == 0);
    aes_enc_desc.done (&sk);
  }

  /* Use the libtommath math descriptor to convert between representations
   * of the Mersenne prime 2^127 - 1 and of a 32-bit value.
   */
  {
    void* a;
    void* b;
    char s[64];
    unsigned char u[16];
    int p;
    size_t i;

    ltc_mp = ltm_desc;

    assert (ltc_mp.init (&a) == CRYPT_OK);
    assert (ltc_mp.init (&b) == CRYPT_OK);

    assert (ltc_mp.read_radix (a, "7FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF", 16) ==
            CRYPT_OK);

    assert (ltc_mp.write_radix (a, s, 10) == CRYPT_OK);
    assert (strcmp (s, "170141183460469231731687303715884105727") == 0);

    assert (ltc_mp.isprime (a, 0, &p) == CRYPT_OK && p == LTC_MP_YES);

    assert (ltc_mp.unsigned_size (a) == sizeof (u));
    assert (ltc_mp.unsigned_write (a, u) == CRYPT_OK);
    assert (u[0] == 0x7f);
    for (i = 1; i != sizeof (u); ++i)
      assert (u[i] == 0xff);

    assert (ltc_mp.unsigned_read (b, u, sizeof (u)) == CRYPT_OK);
    assert (ltc_mp.compare (a, b) == LTC_MP_EQ);

    assert (ltc_mp.set_int (a, 0xdeadbeef) == CRYPT_OK);
    assert (ltc_mp.get_int (a) == 0xdeadbeef);
    assert (ltc_mp.write_radix (a, s, 16) == CRYPT_OK);
    assert (strcmp (s, "DEADBEEF") == 0);

    ltc_mp.deinit (b);
    ltc_mp.deinit (a);
  }

  /* Error reporting.
   */
  assert (strcmp (error_to_string (CRYPT_INVALID_CIPHER),
                  "Invalid cipher specified.") == 0);

  return 0;
}
