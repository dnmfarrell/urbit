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

//TODO: rewrite with more types: purr, wail, body,etc.
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
/* main(): run all test cases.
*/
int
main(int argc, char* argv[])
{
  _setup();

  _test_ames();
  _test_sift_etch_head();

  //  GC
  //
  u3m_grab(u3_none);

  fprintf(stderr, "ames okeedokee\n");
  return 0;
}
