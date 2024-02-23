/**
 * @brief return bool
 */
#define CHECK_LITTLE_ENDIAN() (static_cast<bool>(*("\1\0")))

/**
 * @brief sizeof to bit size
 */
#define SIZE_BIT(type) (sizeof(type) << 3)

/**
 * @brief rotate: UNSIGNED OLNY
 */
#define SHIFT_ROT_L_UNSIGNED(x, move) (((x) << (move)) | ((x) >> (SIZE_BIT((x)) - (move))))

/**
 * @brief rotate: UNSIGNED OLNY
 */
#define SHIFT_ROT_R_UNSIGNED(x, move) (((x) >> (move)) | ((x) << (SIZE_BIT((x)) - (move))))

/**
 * @brief for safe shift: Removes extended filled 1-bit.
 */
#define TO_INT64(x)                                                                                                    \
    (static_cast<unsigned __int64>(x) << ((sizeof(__int64) - sizeof((x))) << 3) >>                                     \
     ((sizeof(unsigned __int64) - sizeof((x))) << 3))

/**
 * @brief shift rotate to left => signed safe
 */
#define SHIFT_ROT_L(x, move) (((TO_INT64(x)) << (move)) | ((TO_INT64(x)) >> (SIZE_BIT((x)) - (move))))

/**
 * @brief shift rotate to right => signed safe
 */
#define SHIFT_ROT_R(x, move) (((TO_INT64(x)) >> (move)) | ((TO_INT64(x)) << (SIZE_BIT((x)) - (move))))

/**
 * @brief e.g. 0x0011 => 0x1100
 */
#define REVERSE_ENDIAN_16(x) (((x) << 8) | (((x) & 0xFF00) >> 8))

/**
 * @brief e.g. 0x00112233 => 0x33221100
 */
#define REVERSE_ENDIAN_32(x)                                                                                           \
    (((x) << 24) | (((x) & 0xFF00) << 8) | (((x) & 0xFF0000) >> 8) | (((x) & 0xFF000000) >> 24))

/**
 * @brief e.g. 0x0011223344556677 => 0x7766554433221100
 */
#define REVERSE_ENDIAN_64(x)                                                                                           \
    (((x) << 56) | (((x) & 0xFF00) << 40) | (((x) & 0xFF0000) << 24) | (((x) & 0xFF000000) << 8) |                     \
     (((x) & 0xFF00000000) >> 8) | (((x) & 0xFF0000000000) >> 24) | (((x) & 0xFF000000000000) >> 40) |                 \
     (((x) & 0xFF00000000000000) >> 56))
