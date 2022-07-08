#ifndef U3_VERE_IO_AMES_INTERNAL_H
#define U3_VERE_IO_AMES_INTERNAL_H

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

//! Fine networking.
typedef struct _u3_fine {
  c3_y              ver_y; //!< fine protocol
  u3p(u3h_root)     sac_p; //!< scry cache hashtable
  struct _u3_ames*  sam_u; //!< ames backpointer
} u3_fine;

//! Ames state.
typedef struct _u3_ames {      //!< packet network state
  u3_auto          car_u;      //!< ames driver
  u3_fine          fin_s;      //!< fine networking
  u3_pier*         pir_u;      //!< pier
  union {                      //!< uv udp handle
    uv_udp_t       wax_u;      //!<
    uv_handle_t    had_u;      //!<
  };
  c3_l             sev_l;      //!< instance number
  ur_cue_test_t*   tes_u;      //!< cue-test handle
  u3_cue_xeno*     sil_u;      //!< cue handle
  c3_c*            dns_c;      //!< domain XX multiple/fallback
  c3_y             ver_y;      //!< protocol version
  u3p(u3h_root)    lax_p;      //!< lane scry cache
  struct _u3_panc* pan_u;      //!< outbound packet queue, backward
  c3_w             imp_w[256]; //!< imperial IPs
  time_t           imp_t[256]; //!< imperial IP timestamps
  c3_o             imp_o[256]; //!< imperial print status
  struct {                     //!< config:
    c3_o           net_o;      //!< can send
    c3_o           see_o;      //!< can scry
    c3_o           fit_o;      //!< filtering active
  } fig_u;
  struct {                     //!< stats:
    c3_d           dop_d;      //!< drop count
    c3_d           fal_d;      //!< crash count
    c3_d           saw_d;      //!< successive scry failures
    c3_d           hed_d;      //!< failed to read header
    c3_d           pre_d;      //!< failed to read prelude
    c3_d           vet_d;      //!< version mismatches filtered
    c3_d           mut_d;      //!< invalid mugs filtered
    c3_d           bod_d;      //!< failed to read body
    c3_d           foq_d;      //!< forward queue size
    c3_d           fow_d;      //!< forwarded count
    c3_d           fod_d;      //!< forwards dropped count
  } sat_u;
} u3_ames;

//! Ames or fine packet header.
typedef struct _u3_head {
  c3_o req_o; //!< is request (fine only)
  c3_o sim_o; //!< is ames protocol?
  c3_y ver_y; //!< protocol version
  c3_y sac_y; //!< sender class
  c3_y rac_y; //!< receiver class
  c3_l mug_l; //!< truncated mug hash of u3_body
  c3_o rel_o; //!< relayed?
} u3_head;

//! Ames/fine packet prelude
typedef struct _u3_prel {
  c3_y  sic_y;    //!< sender life tick
  c3_y  ric_y;    //!< receiver life tick
  c3_d  sen_d[2]; //!< sender/requester
  c3_d  rec_d[2]; //!< receiver/responder
  c3_d  rog_d;    //!< origin lane (optional)
} u3_prel;

//! Unsigned fine request body.
typedef struct _u3_keen {
  c3_w    fra_w; //!< fragment number
  c3_s    len_s; //!< path length
  c3_c*   pat_c; //!< path as ascii
} u3_keen;

//! Signed fine request body.
typedef struct _u3_wail {
  c3_y    sig_y[64]; //!< signature
  u3_keen ken_u;     //!< request payload
} u3_wail;

//! Response portion of purr packet.
typedef struct _u3_meow {
  c3_y    sig_y[64]; //!< host signature
  c3_w    num_w;     //!< number of fragments
  c3_s    siz_s;     //!< datum size (official)
  c3_w    act_s;     //!< datum size (actual)
  c3_y*   dat_y;     //!< datum (0 if null response)
} u3_meow;

//! Fine packet response.
typedef struct _u3_purr {
  u3_keen ken_u;
  u3_meow mew_u;
} u3_purr;

//! Ames packet body.
typedef struct _u3_body {
  c3_s    con_s; //!< content size
  c3_y*   con_y; //!< content
  c3_l    mug_l; //!< checksum
} u3_body;

//! Packet-type tag
typedef enum _u3_ptag {
  PACT_AMES = 1, //!< ames packet
  PACT_WAIL = 2, //!< fine request packet
  PACT_PURR = 3  //!< fine response packet
} u3_ptag;

//! Ames packet.
typedef struct _u3_pact {
  uv_udp_send_t    snd_u; //!< udp send request
  struct _u3_ames* sam_u; //!< ames backpointer
  c3_w             len_w; //!< length in bytes
  c3_y*            hun_y; //!< packet buffer
  u3_head          hed_u; //!< head of packet
  u3_prel          pre_u; //!< packet prelude
  u3_ptag          typ_y; //!< packet type tag
  struct {
    u3_lane        lan_u; //!< destination/origin lane
    c3_y           imp_y; //!< galaxy (optional)
    c3_c*          dns_c; //!< galaxy fqdn (optional)
  } rut_u;
  union {
    u3_body bod_u;        //!< tagged by PACT_AMES
    u3_wail wal_u;        //!< tagged by PACT_WAIL
    u3_purr pur_u;        //!< tagged by PACT_PURR
  };
} u3_pact;

//! Packet queue.
typedef struct _u3_panc {
  struct _u3_panc* pre_u; //!< previous packet
  struct _u3_panc* nex_u; //!< next packet
  u3_pact*         pac_u; //!< this packet
  c3_o             for_o; //!< are we forwarding this?
} u3_panc;

//==============================================================================
// Macros
//==============================================================================

#define _str_o(lob_o) ( ( c3y == lob_o ) ? "yes" : "no" )
#define _str_typ(typ_y) (           \
    ( PACT_AMES == typ_y ) ? "ames" \
  : ( PACT_WAIL == typ_y ) ? "wail" \
  : ( PACT_PURR == typ_y ) ? "purr" : "????")

//==============================================================================
// Functions
//==============================================================================
;
void
_log_head(u3_head* hed_u);

void
_log_prel(u3_prel* pre_u);

void
_log_keen(u3_keen* req_u);

c3_c*
_show_mug_buf(c3_y* buf_y, c3_w len_w);

void
_log_meow(u3_meow* mew_u);

void
_log_bytes(c3_y* byt_y, c3_w len_w);

/* _ames_alloc(): libuv buffer allocator.
*/
void
_ames_alloc(uv_handle_t* had_u,
            size_t len_i,
            uv_buf_t* buf
            );

void
_ames_pact_free(u3_pact* pac_u);

/* _ames_panc_free(): remove references, lose refcounts and free struct
*/
void
_ames_panc_free(u3_panc* pan_u);

u3_ptag
_ames_pact_typ(u3_head* hed_u);

c3_y
_ames_origin_size(u3_head* hed_u);

c3_y
_ames_prel_size(u3_head* hed_u);

c3_s
_ames_body_size(u3_body* bod_u);

c3_s
_fine_keen_size(u3_keen* ken_u);

c3_s
_fine_meow_size(u3_meow* mew_u);

c3_s
_fine_purr_size(u3_purr* pur_u);

c3_o
_ames_check_mug(u3_pact* pac_u);

c3_s
_ames_sift_short(c3_y buf_y[2]);

c3_w
_ames_sift_word(c3_y buf_y[4]);

/* _ames_chub_bytes(): c3_y[8] to c3_d
** XX factor out, deduplicate with other conversions
*/
c3_d
_ames_chub_bytes(c3_y byt_y[8]);

/* _ames_ship_to_chubs(): pack [len_y] bytes into c3_d[2]
*/
void
_ames_ship_to_chubs(c3_d sip_d[2], c3_y len_y, c3_y* buf_y);

/* _ames_chub_bytes(): c3_d to c3_y[8]
** XX factor out, deduplicate with other conversions
*/
void
_ames_bytes_chub(c3_y byt_y[8], c3_d num_d);

/* _ames_ship_of_chubs(): unpack c3_d[2] into [len_y] bytes.
*/
void
_ames_ship_of_chubs(c3_d sip_d[2], c3_y len_y, c3_y* buf_y);

/* _ames_sift_head(): parse packet header.
*/
void
_ames_sift_head(u3_head* hed_u, c3_y buf_y[4]);

/* _ames_sift_prel(): parse prelude,
*/
void
_ames_sift_prel(u3_head* hed_u,
                u3_prel* pre_u,
                c3_y*    buf_y);

/* _fine_sift_wail(): parse request body, returning success
*/
c3_o
_fine_sift_wail(u3_pact* pac_u, c3_w cur_w);

/* _fine_sift_meow(): parse signed scry response fragment
*/
c3_o
_fine_sift_meow(u3_meow* mew_u, u3_noun mew);

void
_ames_etch_short(c3_y buf_y[2], c3_s sot_s);

void
_ames_etch_word(c3_y buf_y[4], c3_w wod_w);

/* _ames_etch_head(): serialize packet header.
*/
void
_ames_etch_head(u3_head* hed_u, c3_y buf_y[4]);

void
_ames_etch_origin(c3_d rog_d, c3_y* buf_y);

/* _ames_etch_prel(): serialize packet prelude
*/
void
_ames_etch_prel(u3_head* hed_u, u3_prel* pre_u, c3_y* buf_y);

/* _fine_etch_keen(): serialize unsigned scry request
*/
void
_fine_etch_keen(u3_keen* ken_u, c3_y* buf_y);

/* fine_etch_meow(): serialize signed scry response fragment
*/
void
_fine_etch_meow(u3_meow* mew_u, c3_y* buf_y);

/* _fine_etch_purr(): serialise response packet
 */
void
_fine_etch_purr(u3_purr* pur_u, c3_y* buf_y);

/* _fine_etch_response(): serialize scry response packet
*/
void
_fine_etch_response(u3_pact* pac_u);

/* _lane_scry_path(): format scry path for retrieving a lane
*/
u3_noun
_lane_scry_path(u3_noun who);

/* _ames_send_cb(): send callback.
*/
void
_ames_send_cb(uv_udp_send_t* req_u, c3_i sas_i);

#define _fine_send _ames_send
/* _ames_send(): send buffer to address on port.
*/
void
_ames_send(u3_pact* pac_u);

/* _ames_lane_into_cache(): put las for who into cache, including timestamp
*/
void
_ames_lane_into_cache(u3p(u3h_root) lax_p, u3_noun who, u3_noun las);

/* _ames_lane_from_cache(): retrieve lane for who from cache, if any & fresh
*/
u3_weak
_ames_lane_from_cache(u3p(u3h_root) lax_p, u3_noun who);

u3_noun
_ames_pact_to_noun(u3_pact* pac_u);

/* _ames_czar_port(): udp port for galaxy.
*/
c3_s
_ames_czar_port(c3_y imp_y);

/* _ames_czar_gone(): galaxy address resolution failed.
*/
void
_ames_czar_gone(u3_pact* pac_u, time_t now);

/* _ames_czar_here(): galaxy address resolution succeeded.
*/
void
_ames_czar_here(u3_pact* pac_u, time_t now, struct sockaddr_in* add_u);

/* _ames_czar_cb(): galaxy address resolution callback.
*/
void
_ames_czar_cb(uv_getaddrinfo_t* adr_u,
              c3_i              sas_i,
              struct addrinfo*  aif_u);

/* _ames_czar(): galaxy address resolution.
*/
void
_ames_czar(u3_pact* pac_u);

/* _fine_put_cache(): put list of packets into cache
 */
void
_fine_put_cache(u3_ames* sam_u, u3_noun pax, c3_w lop_w, u3_noun lis);

/* _ames_ef_send(): send packet to network (v4).
*/
void
_ames_ef_send(u3_ames* sam_u, u3_noun lan, u3_noun pac);

/* _ames_cap_queue(): cap ovum queue at 1k, dropping oldest packets.
*/
void
_ames_cap_queue(u3_ames* sam_u);

/* _ames_punt_goof(): print %bail error report(s).
*/
void
_ames_punt_goof(u3_noun lud);

/* _ames_hear_bail(): handle packet failure.
*/
void
_ames_hear_bail(u3_ovum* egg_u, u3_noun lud);

/* _ames_put_packet(): add packet to queue, drop old packets on pressure
*/
void
_ames_put_packet(u3_ames* sam_u,
                 u3_noun  msg,
                 u3_lane  lan_u);

/* _ames_send_many(): send pac_u on the (list lane) las; retains pac_u
*/
void
_ames_send_many(u3_pact* pac_u, u3_noun las, c3_o for_o);

/*  _ames_lane_scry_cb(): learn lanes to send packet on
*/
void
_ames_lane_scry_cb(void* vod_p, u3_noun nun);

/* _ames_try_send(): try to send a packet to a ship and its sponsors
*/
void
_ames_try_send(u3_pact* pac_u, c3_o for_o);

#undef AMES_SKIP
#ifdef AMES_SKIP
/* _ames_skip(): decide whether to skip this packet, for rescue
*/
c3_o
_ames_skip(u3_prel* pre_u);
#endif

/* _fine_lop(): find beginning of page containing fra_w
*/
c3_w
_fine_lop(c3_w fra_w);

u3_weak
_fine_scry_path(u3_pact* pac_u, c3_o lop_o);

/* _fine_pack_scry_cb(): receive packets for datum out of fine
 */
void _fine_pack_scry_cb(void* vod_p, u3_noun nun);

//  TODO: check protocol version
void
_fine_hear_request(u3_pact* req_u, c3_w cur_w);

//  TODO: check protocol version
void
_fine_hear_response(u3_pact* pac_u, c3_w cur_w);

void
_ames_hear_ames(u3_pact* pac_u, c3_w cur_w);

void
_ames_try_forward(u3_pact* pac_u);

/* _ames_hear(): parse a (potential) packet, dispatch appropriately.

  packet filtering needs to revised for two protocol-change scenarios

    - packets using old protocol versions from our sponsees
      these must be let through, and this is a transitive condition;
      they must also be forwarded where appropriate
      they can be validated, as we know their semantics

    - packets using newer protocol versions
      these should probably be let through, or at least
      trigger printfs suggesting upgrade.
      they cannot be filtered, as we do not know their semantics
*/
void
_ames_hear(u3_ames* sam_u,
           u3_lane* lan_u,
           c3_w     len_w,
           c3_y*    hun_y);

/* _ames_recv_cb(): udp message receive callback.
*/
void
_ames_recv_cb(uv_udp_t*        wax_u,
              ssize_t          nrd_i,
              const uv_buf_t * buf_u,
              const struct sockaddr* adr_u,
              unsigned         flg_i);

/* _ames_io_start(): initialize ames I/O.
*/
void
_ames_io_start(u3_ames* sam_u);

/* _ames_ef_turf(): initialize ames I/O on domain(s).
*/
void
_ames_ef_turf(u3_ames* sam_u, u3_noun tuf);


/* _ames_prot_scry_cb(): receive ames protocol version
*/
void
_ames_prot_scry_cb(void* vod_p, u3_noun nun);

/* _fine_prot_scry_cb(): receive fine protocol version
*/
void
_fine_prot_scry_cb(void* vod_p, u3_noun nun);

/* _ames_io_talk(): start receiving ames traffic.
*/
void
_ames_io_talk(u3_auto* car_u);

/* _ames_kick_newt(): apply packet network outputs.
*/
c3_o
_ames_kick_newt(u3_ames* sam_u, u3_noun tag, u3_noun dat);

/* _ames_io_kick(): apply effects
*/
c3_o
_ames_io_kick(u3_auto* car_u, u3_noun wir, u3_noun cad);

/* _ames_exit_cb(): dispose resources aftr close.
*/
void
_ames_exit_cb(uv_handle_t* had_u);

/* _ames_io_exit(): terminate ames I/O.
*/
void
_ames_io_exit(u3_auto* car_u);

/* _ames_io_info(): produce status info.
*/
u3_noun
_ames_io_info(u3_auto* car_u);

/* _ames_io_slog(): print status info.
*/
void
_ames_io_slog(u3_auto* car_u);

/* _u3_ames_lane_to_chub(): serialize lane to double-word
*/
c3_d
_u3_ames_lane_to_chub(u3_lane lan);

/* _u3_ames_encode_lane(): serialize lane to noun
*/
u3_atom
_u3_ames_encode_lane(u3_lane lan);

/* _u3_ames_decode_lane(): deserialize noun to lane; 0.0.0.0:0 if invalid
*/
u3_lane
_u3_ames_decode_lane(u3_atom lan);

#endif /* ifndef U3_VERE_IO_AMES_INTERNAL_H */
