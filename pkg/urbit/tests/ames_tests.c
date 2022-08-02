#include "all.h"
#include "vere/io/ames_private.h"
#include "vere/vere.h"

/* _setup(): prepare for tests.
*/
static void
_setup(void)
{
  u3m_init();
  u3m_pave(c3y);
}

/* _test_ames(): spot check ames helpers
*/
static void
_test_ames(void)
{
  u3_lane lan_u;
  lan_u.pip_w = 0x7f000001;
  lan_u.por_s = 12345;

  u3_noun lan = _u3_ames_encode_lane(lan_u);
  u3_lane nal_u = _u3_ames_decode_lane(u3k(lan));
  u3_lane nal_u2 = _u3_ames_decode_lane(lan);

  if ( !(lan_u.pip_w == nal_u.pip_w && lan_u.por_s == nal_u.por_s) ) {
    fprintf(stderr, "ames: lane fail (a)\r\n");
    fprintf(stderr, "pip: %d, por: %d\r\n", nal_u.pip_w, nal_u.por_s);
    exit(1);
  }
}

static void
_test_sift_etch_head()
{
  u3_head* hed_u = c3_calloc(sizeof(*hed_u));
  hed_u->req_o = c3n;
  hed_u->sim_o = c3y;
  hed_u->ver_y = 0;
  hed_u->sac_y = 3;
  hed_u->rac_y = 3;
  hed_u->mug_l = 4;
  hed_u->rel_o = c3n;

  c3_y* out_y = c3_calloc(sizeof(*out_y) * 4);
  _ames_etch_head(hed_u, out_y);

  u3_head* nhed_u = c3_calloc(sizeof(*nhed_u));
  _ames_sift_head(nhed_u, out_y);

 if( 0 != memcmp(hed_u, nhed_u, sizeof(*hed_u))) {
   fprintf(stderr, "ames: header serialisation mismatch(a)\r\n");
   _log_head(hed_u);
   _log_head(nhed_u);
   exit(1);
 }
}

static void
_test_sift_etch_prel()
{
  u3_head* hed_u = c3_calloc(sizeof(*hed_u));
  hed_u->sac_y = 0; // galaxy/sun
  hed_u->rac_y = 1; // planet
  hed_u->rel_o = c3n;

  u3_prel* pre_u = c3_calloc(sizeof(*pre_u));
  pre_u->sic_y = 1;             // sender life tick
  pre_u->ric_y = 0;             // recevr life tick
  pre_u->sen_d[0] = 0x1;        // nec
  pre_u->rec_d[0] = 0x60daf13f; // sampel-palnet

  c3_y* out_y = c3_calloc(sizeof(*out_y) * 7); // 1 ticks, 2 galaxy, 4 planet
  _ames_etch_prel(hed_u, pre_u, out_y);

  u3_prel* npre_u = c3_calloc(sizeof(*npre_u));
  _ames_sift_prel(hed_u, npre_u, out_y);

  if( 0 != memcmp(pre_u, npre_u, sizeof(*pre_u))) {
    fprintf(stderr, "ames: prelude mismatch\r\n");
    _log_prel(pre_u);
    _log_prel(npre_u);
    exit(1);
  }

  // with optional origin lane
  hed_u->rel_o = c3y;
  c3_d lan_d = 0x6a267a93;
  pre_u->rog_d = lan_d << 4 ^ 12345;
  c3_y* nout_y = c3_calloc(sizeof(*nout_y) * 13); // 1 ticks, 2 galaxy, 4 planet, 6 lane
  _ames_etch_prel(hed_u, pre_u, nout_y);

  _ames_sift_prel(hed_u, npre_u, nout_y);

  if( 0 != memcmp(pre_u, npre_u, sizeof(*pre_u))) {
    fprintf(stderr, "ames: prelude with origin lane mismatch\r\n");
    _log_prel(pre_u);
    _log_prel(npre_u);
    exit(1);
  }
}

static void
_test_etch_keen()
{
  u3_keen* ken_u = c3_calloc(sizeof(*ken_u));
  ken_u->fra_w = 1;
  ken_u->len_s = 5;
  ken_u->pat_c = "/foo";

  c3_y* out_y = c3_calloc(sizeof(*out_y) * 11); // 4 fragment, 2 len, 5 path
  _fine_etch_keen(ken_u, out_y);

  // our own sift_keen
  u3_keen* nken_u = c3_calloc(sizeof(*nken_u));
  nken_u->fra_w = _ames_sift_word(out_y);
  nken_u->len_s = _ames_sift_short(out_y+4);
  nken_u->pat_c = c3_calloc(sizeof(c3_c) * (nken_u->len_s));
  memcpy(nken_u->pat_c, out_y+6, nken_u->len_s);

  if( 0 != memcmp(ken_u, nken_u, 6)) { // 4 fragment, 2 len
    fprintf(stderr, "ames: keen serialisation mismatch\r\n");
    _log_keen(ken_u);
    _log_keen(nken_u);
    exit(1);
  }
  if( 0 != memcmp(ken_u->pat_c, nken_u->pat_c, ken_u->len_s)) {
    fprintf(stderr, "ames: keen paths mismatch\r\n");
    _log_keen(ken_u);
    _log_keen(nken_u);
    exit(1);
  }
}

static void
_test_sift_wail()
{
  u3_pact* pac_u = c3_calloc(sizeof(*pac_u));
  pac_u->len_w = 75;// 64 sig, 4 fra, 2 len, 5 pat
  pac_u->hun_y = c3_calloc(sizeof(c3_y) * pac_u->len_w);
  pac_u->hun_y[0]  = 1;                // sig
  pac_u->hun_y[64] = 2;                // fra
  pac_u->hun_y[68] = 5;                // len
  memcpy(&pac_u->hun_y[70], "/foo", 5);// pat

  c3_o suc_o = _fine_sift_wail(pac_u, 0);
  if ( 0 != suc_o) {
    fprintf(stderr, "ames: sift wail return failure\r\n");
    exit(1);
  }
  if( pac_u->wal_u.sig_y[0] != 1) {
    fprintf(stderr, "ames: sift wail signature mismatch\r\n");
    exit(1);
  }
  if( 0 != strcmp("/foo", pac_u->wal_u.ken_u.pat_c)) {
    fprintf(stderr, "ames: sift wail keen paths mismatch\r\n");
    exit(1);
  }
}

static void
_test_etch_meow()
{
  u3_meow* mew_u = c3_calloc(sizeof(*mew_u));
  mew_u->sig_y[0] = 1;
  mew_u->num_w = 1;     //!< number of fragments
  mew_u->siz_s = 1;     //!< datum size (official)
  mew_u->act_s = 1;     //!< datum size (actual)
  mew_u->dat_y = c3_malloc(sizeof(c3_y) * 1);     //!< datum (0 if null response)
  mew_u->dat_y[0] = 117; // u

  c3_y* out_y = c3_calloc(sizeof(*out_y) * 71);
  _fine_etch_meow(mew_u, out_y);

 if( mew_u->dat_y[0] != out_y[70]) {
   fprintf(stderr, "ames: meow serialisation mismatch\r\n");
   _log_meow(mew_u);
   exit(1);
 }
}

/* main(): run all test cases.
*/
int
main(int argc, char* argv[])
{
  _setup();

  _test_ames();
  _test_sift_etch_head();
  _test_sift_etch_prel();
  _test_etch_meow(); // sift returns noun?
  _test_etch_keen(); // no sift_keen()
  _test_sift_wail(); // no etch_wail()

  //  GC
  //
  u3m_grab(u3_none);

  fprintf(stderr, "ames okeedokee\n");
  return 0;
}
