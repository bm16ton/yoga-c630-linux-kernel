// DriConf options specific to radeonsi
DRI_CONF_SECTION_PERFORMANCE
DRI_CONF_ADAPTIVE_SYNC("true")
DRI_CONF_RADEONSI_ASSUME_NO_Z_FIGHTS("false")
DRI_CONF_RADEONSI_COMMUTATIVE_BLEND_ADD("false")
DRI_CONF_RADEONSI_ZERO_ALL_VRAM_ALLOCS("false")
DRI_CONF_SECTION_END

DRI_CONF_SECTION_DEBUG

//= BEGIN VERBATIM
#define OPT_BOOL(name, dflt, description)                                                          \
   DRI_CONF_OPT_BEGIN_B(radeonsi_##name, #dflt)                                                    \
   DRI_CONF_DESC(en, description)                                                                  \
   DRI_CONF_OPT_END

#include "radeonsi/si_debug_options.h"
//= END VERBATIM

DRI_CONF_SECTION_END
