DESCRIPTION = "AV codec lib"
HOMEPAGE = "http://nohomepage.org"
SECTION = "Multimedia/Codec"
LICENSE = "LGPL-2.1+"
PV = "9.8"

SRC_URI = ""

S = "${WORKDIR}/git"

inherit manifest autotools-brokensep

BBCLASSEXTEND = ""
PROVIDES = ""

#PROVIDES by libavutil
PROVIDES += "libavutil"


#PROVIDES by libavfilter-dev
PROVIDES += "libavfilter-dev"


#PROVIDES by libavformat
PROVIDES += "libavformat"


#PROVIDES by libavtools
PROVIDES += "libavtools"


#PROVIDES by libavcodec
PROVIDES += "libavcodec"


#PROVIDES by libavfilter
PROVIDES += "libavfilter"


#PROVIDES by libswscale-dev
PROVIDES += "libswscale-dev"


#PROVIDES by libavcodec-dev
PROVIDES += "libavcodec-dev"


#PROVIDES by libavutil-dev
PROVIDES += "libavutil-dev"


#PROVIDES by libswscale
PROVIDES += "libswscale"


#PROVIDES by libav


#PROVIDES by libavformat-dev
PROVIDES += "libavformat-dev"


RDEPENDS = ""
#RDEPENDS of libavfilter-dev (${PN}filter-dev)
RDEPENDS_${PN}filter-dev += "libavfilter"

#RDEPENDS of libswscale-dev (libswscale-dev)
RDEPENDS_libswscale-dev += "libswscale"

#RDEPENDS of libavcodec-dev (${PN}codec-dev)
RDEPENDS_${PN}codec-dev += "libavcodec"

#RDEPENDS of libavutil-dev (${PN}util-dev)
RDEPENDS_${PN}util-dev += "libavutil"

#RDEPENDS of libavformat-dev (${PN}format-dev)
RDEPENDS_${PN}format-dev += "libavformat"


DEPENDS = ""

do_prep() {
 cd ${S}
 chmod -Rf a+rX,u+w,g-w,o-w ${S}
 #setup -q
 cp ${S}/packaging/libav.manifest .
 
 
}
do_patch_append() {
    bb.build.exec_func('do_prep', d)
}

do_configure() {
}

do_compile() {
 cd ${S}
 LANG=C
 export LANG
 unset DISPLAY
 LD_AS_NEEDED=1; export LD_AS_NEEDED ;
 
 export CONFIGURE_OPTIONS="--enable-shared    --disable-static   \
 --disable-version3  --disable-devices   --disable-nonfree --disable-gpl --disable-doc \
 --disable-zlib    --disable-network \
 --disable-avdevice \
 --disable-bsfs      --disable-filters \
 --enable-filter=buffer  --enable-filter=buffersink      --enable-filter=crop \
 --enable-filter=hflip   --enable-filter=lut     --enable-filter=lutyuv \
 --enable-filter=lutrgb  --enable-filter=overlay --enable-filter=scale \
 --enable-filter=transpose       --enable-filter=unsharp --enable-filter=vflip \
 --disable-protocols \
 --disable-avresample \
 --enable-protocol=file \
 --disable-encoders \
 --disable-muxers \
 --disable-parsers \
 --enable-parser=aac     --enable-parser=h264            --enable-parser=mpegaudio \
 --enable-parser=h263    --enable-parser=mpeg4video      --enable-parser=mpegvideo \
 --disable-demuxers \
 --enable-demuxer=aac    --enable-demuxer=h264   --enable-demuxer=mpegts \
 --enable-demuxer=amr    --enable-demuxer=m4v    --enable-demuxer=mpegtsraw \
 --enable-demuxer=asf    --enable-demuxer=mmf    --enable-demuxer=mpegvideo \
 --enable-demuxer=avi    --enable-demuxer=mov    --enable-demuxer=ogg \
 --enable-demuxer=flac   --enable-demuxer=mp3    --enable-demuxer=wav \
 --enable-demuxer=h263   --enable-demuxer=mpegps --enable-demuxer=matroska \
 --enable-demuxer=dv	--enable-demuxer=flv \
 --disable-decoders \
 --enable-decoder=alac   --enable-decoder=h264           --enable-decoder=wmv1 \
 --enable-decoder=flac   --enable-decoder=mpeg4          --enable-decoder=wmv2 \
 --enable-decoder=h263   --enable-decoder=mpegvideo      --enable-decoder=wmv3 \
 --enable-decoder=vc1	--enable-decoder=flv \
 --enable-decoder=h263i  --enable-decoder=theora  \
 --enable-decoder=pcm_alaw  --enable-decoder=pcm_mulaw  \
 --enable-encoder=h263   --enable-encoder=h263p  --enable-encoder=mpeg4   \
 --enable-decoder=bmp  --enable-encoder=bmp       \
 --enable-decoder=tiff \
 --enable-decoder=mp3  --enable-decoder=amrnb    \
 --enable-encoder=aac  --enable-decoder=aac      \
 --enable-swscale        --disable-yasm	 \
 --enable-fft    --enable-rdft   --enable-mdct   --enable-neon \
 "
 
 
 CFLAGS="$CFLAGS -fPIC -DEXPORT_API=\"__attribute__((visibility(\\\"default\\\")))\" "; export CFLAGS
 
 ./configure --prefix=${prefix} --shlibdir=${prefix}/lib --libdir=${prefix}/lib  $CONFIGURE_OPTIONS
 
 oe_runmake ${PARALLEL_MAKE}
 
 
 
}

do_install() {
 export RPM_BUILD_ROOT=${D}
 cd ${S}
 LANG=C
 export LANG
 unset DISPLAY
 rm -rf ${D}
 mkdir -p ${D}
 
 rm -rf ${D}
 
   oe_runmake \
         DESTDIR=${D} \
         INSTALL_ROOT=${D} \
         BINDIR=${prefix}/bin \
   install  
   rm -f ${D}${infodir}/dir 
   find ${D} -regex ".*\.la$" | xargs rm -f -- 
   find ${D} -regex ".*\.a$" | xargs rm -f --
 mkdir -p ${D}${prefix}/share/license
 cp -rf ${WORKDIR}/libav-9.8/COPYING.LGPLv2.1 ${D}${prefix}/share/license/libavcodec
 cp -rf ${WORKDIR}/libav-9.8/COPYING.LGPLv2.1 ${D}${prefix}/share/license/libavformat
 cp -rf ${WORKDIR}/libav-9.8/COPYING.LGPLv2.1 ${D}${prefix}/share/license/libavutil
 cp -rf ${WORKDIR}/libav-9.8/COPYING.LGPLv2.1 ${D}${prefix}/share/license/libavfilter
 cp -rf ${WORKDIR}/libav-9.8/COPYING.LGPLv2.1 ${D}${prefix}/share/license/libswscale
 
 
}

pkg_postinst_libavfilter() {
    #!/bin/sh -e

    [ "x$D" == "x" ] && ldconfig
}

pkg_postinst_${PN}() {
    #!/bin/sh -e

    [ "x$D" == "x" ] && ldconfig
}

pkg_postinst_libavutil() {
    #!/bin/sh -e

    [ "x$D" == "x" ] && ldconfig
}

pkg_postinst_libavcodec() {
    #!/bin/sh -e

    [ "x$D" == "x" ] && ldconfig
}

pkg_postinst_libswscale() {
    #!/bin/sh -e

    [ "x$D" == "x" ] && ldconfig
}

pkg_postinst_libavformat() {
    #!/bin/sh -e

    [ "x$D" == "x" ] && ldconfig
}

pkg_postrm_libavfilter() {
    #!/bin/sh -e

    [ "x$D" == "x" ] && ldconfig
}

pkg_postrm_${PN}() {
    #!/bin/sh -e

    [ "x$D" == "x" ] && ldconfig
}

pkg_postrm_libavcodec() {
    #!/bin/sh -e

    [ "x$D" == "x" ] && ldconfig
}

pkg_postrm_libswscale() {
    #!/bin/sh -e

    [ "x$D" == "x" ] && ldconfig
}

pkg_postrm_libavformat() {
    #!/bin/sh -e

    [ "x$D" == "x" ] && ldconfig
}

pkg_postrm_libavutil() {
    #!/bin/sh -e

    [ "x$D" == "x" ] && ldconfig
}

PACKAGES = "${PN}-dbg ${PN}-doc ${PN}-locale"
PACKAGES += " libavutil "
PACKAGES += " libavfilter-dev "
PACKAGES += " libavformat "
PACKAGES += " libavtools "
PACKAGES += " libavcodec "
PACKAGES += " libavfilter "
PACKAGES += " libswscale-dev "
PACKAGES += " libavcodec-dev "
PACKAGES += " libavutil-dev "
PACKAGES += " libswscale "
PACKAGES += " libavformat-dev "

libavutil_files = ""
libavutil_files += "${prefix}/lib/libavutil.so.*"
libavutil_files += "${prefix}/share/license/libavutil"
MANIFESTFILES_${PN}util = "libav.manifest"

libavfilter-dev_files = ""
libavfilter-dev_files += "${prefix}/include/libavfilter/*"
libavfilter-dev_files += "${prefix}/lib/libavfilter.so"
libavfilter-dev_files += "${prefix}/lib/pkgconfig/libavfilter.pc"
MANIFESTFILES_${PN}filter-dev = "libav.manifest"

libavformat_files = ""
libavformat_files += "${prefix}/lib/libavformat.so.*"
libavformat_files += "${prefix}/share/license/libavformat"
MANIFESTFILES_${PN}format = "libav.manifest"

libavtools_files = ""
libavtools_files += "${prefix}/bin/av*"
libavtools_files += "${prefix}/share/avconv/*.avpreset"
MANIFESTFILES_${PN}tools = "libav.manifest"

libavcodec_files = ""
libavcodec_files += "${prefix}/lib/libavcodec.so.*"
libavcodec_files += "${prefix}/share/license/libavcodec"
MANIFESTFILES_${PN}codec = "libav.manifest"

libavfilter_files = ""
libavfilter_files += "${prefix}/lib/libavfilter.so.*"
libavfilter_files += "${prefix}/share/license/libavfilter"
MANIFESTFILES_${PN}filter = "libav.manifest"

libswscale-dev_files = ""
libswscale-dev_files += "${prefix}/include/libswscale/*"
libswscale-dev_files += "${prefix}/lib/libswscale.so"
libswscale-dev_files += "${prefix}/lib/pkgconfig/libswscale.pc"
MANIFESTFILES_libswscale-dev = "libav.manifest"

libavcodec-dev_files = ""
libavcodec-dev_files += "${prefix}/include/libavcodec/*"
libavcodec-dev_files += "${prefix}/lib/libavcodec.so"
libavcodec-dev_files += "${prefix}/lib/pkgconfig/libavcodec.pc"
MANIFESTFILES_${PN}codec-dev = "libav.manifest"

libavutil-dev_files = ""
libavutil-dev_files += "${prefix}/include/libavutil/*"
libavutil-dev_files += "${prefix}/lib/libavutil.so"
libavutil-dev_files += "${prefix}/lib/pkgconfig/libavutil.pc"
MANIFESTFILES_${PN}util-dev = "libav.manifest"

libswscale_files = ""
libswscale_files += "${prefix}/lib/libswscale.so.*"
libswscale_files += "${prefix}/share/license/libswscale"
MANIFESTFILES_libswscale = "libav.manifest"

libavformat-dev_files = ""
libavformat-dev_files += "${prefix}/include/libavformat/*"
libavformat-dev_files += "${prefix}/lib/libavformat.so"
libavformat-dev_files += "${prefix}/lib/pkgconfig/libavformat.pc"
MANIFESTFILES_${PN}format-dev = "libav.manifest"

FILES_${PN}util = "${libavutil_files}"
FILES_${PN}filter-dev = "${libavfilter-dev_files}"
FILES_${PN}format = "${libavformat_files}"
FILES_${PN}tools = "${libavtools_files}"
FILES_${PN}codec = "${libavcodec_files}"
FILES_${PN}filter = "${libavfilter_files}"
FILES_libswscale-dev = "${libswscale-dev_files}"
FILES_${PN}codec-dev = "${libavcodec-dev_files}"
FILES_${PN}util-dev = "${libavutil-dev_files}"
FILES_libswscale = "${libswscale_files}"
FILES_${PN}format-dev = "${libavformat-dev_files}"

PKG_libavutil= "libavutil"
PKG_libavfilter-dev= "libavfilter-dev"
PKG_libavformat= "libavformat"
PKG_libavtools= "libavtools"
PKG_libavcodec= "libavcodec"
PKG_libavfilter= "libavfilter"
PKG_libswscale-dev= "libswscale-dev"
PKG_libavcodec-dev= "libavcodec-dev"
PKG_libavutil-dev= "libavutil-dev"
PKG_libswscale= "libswscale"
PKG_libavformat-dev= "libavformat-dev"

require libav-extraconf.inc

