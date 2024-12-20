#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

// Defines how many zeroes we need a the front of hash for
// proof of work
#define REQUIREDZEROES 4
#define HASH_STRING_LENGTH 65

// Defines macros for rotations
#define ROTLEFT(a, b) (((a) << (b)) | ((a) >> (32 - (b))))
#define ROTRIGHT(a, b) (((a) >> (b)) | ((a) << (32 - (b))))

// Defines logical functions for SHA-256's main operations
#define CH(x, y, z) (((x) & (y)) ^ (~(x) & (z)))
#define MAJ(x, y, z) (((x) & (y)) ^ ((x) & (z)) ^ ((y) & (z)))
#define EP0(x) (ROTRIGHT(x, 2) ^ ROTRIGHT(x, 13) ^ ROTRIGHT(x, 22))
#define EP1(x) (ROTRIGHT(x, 6) ^ ROTRIGHT(x, 11) ^ ROTRIGHT(x, 25))
#define SIG0(x) (ROTRIGHT(x, 7) ^ ROTRIGHT(x, 18) ^ ((x) >> 3))
#define SIG1(x) (ROTRIGHT(x, 17) ^ ROTRIGHT(x, 19) ^ ((x) >> 10))

// Defines all constants needed for SHA-256 (k values for each round)
static const uint32_t k[64] = {
    0x428a2f98, 0x71374491, 0xb5c0fbcf, 0xe9b5dba5,
    0x3956c25b, 0x59f111f1, 0x923f82a4, 0xab1c5ed5,
    0xd807aa98, 0x12835b01, 0x243185be, 0x550c7dc3,
    0x72be5d74, 0x80deb1fe, 0x9bdc06a7, 0xc19bf174,
    0xe49b69c1, 0xefbe4786, 0x0fc19dc6, 0x240ca1cc,
    0x2de92c6f, 0x4a7484aa, 0x5cb0a9dc, 0x76f988da,
    0x983e5152, 0xa831c66d, 0xb00327c8, 0xbf597fc7,
    0xc6e00bf3, 0xd5a79147, 0x06ca6351, 0x14292967,
    0x27b70a85, 0x2e1b2138, 0x4d2c6dfc, 0x53380d13,
    0x650a7354, 0x766a0abb, 0x81c2c92e, 0x92722c85,
    0xa2bfe8a1, 0xa81a664b, 0xc24b8b70, 0xc76c51a3,
    0xd192e819, 0xd6990624, 0xf40e3585, 0x106aa070,
    0x19a4c116, 0x1e376c08, 0x2748774c, 0x34b0bcb5,
    0x391c0cb3, 0x4ed8aa4a, 0x5b9cca4f, 0x682e6ff3,
    0x748f82ee, 0x78a5636f, 0x84c87814, 0x8cc70208,
    0x90befffa, 0xa4506ceb, 0xbef9a3f7, 0xc67178f2
};

// Structure for SHA-256 context (holds state, data, and bit length)
typedef struct {
    uint8_t data[64];
    uint32_t datalen;
    uint64_t bitlen;
    uint32_t state[8];
} SHA256_CTX;

// Function prototypes for SHA-256 operations

// Initializes the SHA-256 context with initial state values
void sha256_init(SHA256_CTX *ctx);

// Main transformation function that processes a 512-bit chunk of data
void sha256_transform(SHA256_CTX *ctx, const uint8_t data[]);

// Updates the SHA-256 context with new data to be hashed
void sha256_update(SHA256_CTX *ctx, const uint8_t data[], size_t len);

// Finalizes the SHA-256 hashing process and produces the hash
void sha256_final(SHA256_CTX *ctx, uint8_t hash[]);

// High-level function to compute the SHA-256 hash of a string and modifies second arg
// so that it contains 32 8-bit values
void sha256(const char* input, uint8_t hash[]);

/**
 * compares two sets of hashes and returns true or false
 * @pre hash1 and hash2 both have an allocation of at least 32
 * @post returns true iff the first 32 elements of hash1 and hash2 are equal
 */
bool compareHashes(uint8_t hash1[], uint8_t hash2[]);

// determines whethere a hash meets the proof of work standard defined in the header
/**
 * determines whethere a hash meets the proof of work standard defined in the header
 * @pre hash has at least an allocation for 32 elements
 * @post returns true iff the first {REQUIREDZEROES} elements of hash == 0
 */
bool meetsProofOfWork(uint8_t hash[]);

/**
 * based on the hash it creates a string this requires that dest has an allocation for 65 chars
 * @pre hash at least 32 elements
 * @pre dest has an allocation for at least 65 elements
 * @post dest will correspond with the hexadecimal output of hash and end will null terminating
 */
void makeHashString(uint8_t hash[], char* dest);

/**
 * initializes all values in the hash array to 0
 * @pre hash at least 32 elements
 * @post the first 32 elements of hash will be equal to 0
 */
void initializeHash(uint8_t hash[]);

/**
 * copies all the values in hash1 into hash2
 * @pre hash1 has at least 32 elements
 * @pre hash2 has at least 32 elements
 * @post the first 32 elemetns of hash2 will equal the first 32 elements of hash1
 */
void copyHashes(uint8_t hash1[], uint8_t hash2[]);
