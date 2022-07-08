#ifndef U3_VERE_IO_AMES_H
#define U3_VERE_IO_AMES_H

#include "all.h"
#include "ur/serial.h"
#include "vere/vere.h"

//==============================================================================
// Types
//==============================================================================

//! Ames lane (IP address and port).
typedef struct _u3_lane {
  c3_w             pip_w; //!< target IPv4 address
  c3_s             por_s; //!< target port
} u3_lane;

//==============================================================================
// Functions
//==============================================================================

//! Initialize ames I/O.
u3_auto*
u3_ames_io_init(u3_pier*);

//! Decode lane from noun.
u3_lane
u3_ames_decode_lane(u3_noun);

//! Encode lane as noun.
u3_noun
u3_ames_encode_lane(u3_lane);

#endif /* ifndef U3_VERE_IO_AMES_H */
