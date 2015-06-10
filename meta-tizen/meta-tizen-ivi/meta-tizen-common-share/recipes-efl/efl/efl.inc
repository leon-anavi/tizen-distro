DESCRIPTION = "Enlightenment Foundation Libraries - set of libraries used (not only) by E17"
HOMEPAGE = "http://enlightenment.org/"
SECTION = "Graphics & UI Framework/API"
LICENSE = "LGPL-2.1"
PV = "1.9.3"

SRC_URI = ""

S = "${WORKDIR}/git"

inherit manifest autotools-brokensep

BBCLASSEXTEND = ""
PROVIDES = ""

#PROVIDES by edje
PROVIDES += "edje"


#PROVIDES by ephysics-examples
PROVIDES += "ephysics-examples"


#PROVIDES by eo
PROVIDES += "eo"


#PROVIDES by ephysics-dev
PROVIDES += "ephysics-dev"


#PROVIDES by emotion-dev
PROVIDES += "emotion-dev"


#PROVIDES by eina
PROVIDES += "eina"


#PROVIDES by eina-examples
PROVIDES += "eina-examples"


#PROVIDES by eo-examples
PROVIDES += "eo-examples"


#PROVIDES by eet-dev
PROVIDES += "eet-dev"


#PROVIDES by ephysics
PROVIDES += "ephysics"


#PROVIDES by eeze-dev
PROVIDES += "eeze-dev"


#PROVIDES by efl


#PROVIDES by efreet-dev
PROVIDES += "efreet-dev"


#PROVIDES by ecore-dev
PROVIDES += "ecore-dev"


#PROVIDES by ethumb-examples
PROVIDES += "ethumb-examples"


#PROVIDES by ethumb
PROVIDES += "ethumb"


#PROVIDES by evas-dev
PROVIDES += "evas-dev"


#PROVIDES by efl-data
PROVIDES += "efl-data"


#PROVIDES by evas
PROVIDES += "evas"


#PROVIDES by eeze
PROVIDES += "eeze"


#PROVIDES by ethumb-dev
PROVIDES += "ethumb-dev"


#PROVIDES by efreet
PROVIDES += "efreet"


#PROVIDES by eldbus-dev
PROVIDES += "eldbus-dev"


#PROVIDES by eet-examples
PROVIDES += "eet-examples"


#PROVIDES by embryo-dev
PROVIDES += "embryo-dev"


#PROVIDES by eio-dev
PROVIDES += "eio-dev"


#PROVIDES by ecore-examples
PROVIDES += "ecore-examples"


#PROVIDES by emotion
PROVIDES += "emotion"


#PROVIDES by eldbus-examples
PROVIDES += "eldbus-examples"


#PROVIDES by eo-dev
PROVIDES += "eo-dev"


#PROVIDES by embryo
PROVIDES += "embryo"
# the PROVIDES rules is ignore "embryo-bin  "
PROVIDES += "embryo-bin"
RPROVIDES_embryo += "embryo-bin"


#PROVIDES by eio-examples
PROVIDES += "eio-examples"


#PROVIDES by eet-tools
PROVIDES += "eet-tools"
# the PROVIDES rules is ignore "eet-bin  "
PROVIDES += "eet-bin"
RPROVIDES_eet-tools += "eet-bin"


#PROVIDES by edje-dev
PROVIDES += "edje-dev"


#PROVIDES by edje-tools
PROVIDES += "edje-tools"
# the PROVIDES rules is ignore "edje-bin  "
PROVIDES += "edje-bin"
RPROVIDES_edje-tools += "edje-bin"


#PROVIDES by eet
PROVIDES += "eet"


#PROVIDES by eina-dev
PROVIDES += "eina-dev"


#PROVIDES by evas-examples
PROVIDES += "evas-examples"


#PROVIDES by emotion-examples
PROVIDES += "emotion-examples"


#PROVIDES by ecore
PROVIDES += "ecore"


#PROVIDES by eldbus
PROVIDES += "eldbus"


#PROVIDES by edje-examples
PROVIDES += "edje-examples"


#PROVIDES by eio
PROVIDES += "eio"


RDEPENDS = ""
#RDEPENDS of edje (edje)
RDEPENDS_edje += "efl-data"

#RDEPENDS of ephysics-examples (ephysics-examples)
RDEPENDS_ephysics-examples += "ephysics"

#RDEPENDS of eo (eo)
RDEPENDS_eo += "efl-data"

#RDEPENDS of ephysics-dev (ephysics-dev)
RDEPENDS_ephysics-dev += "ephysics"

#RDEPENDS of emotion-dev (emotion-dev)
RDEPENDS_emotion-dev += "emotion"

#RDEPENDS of eina (eina)
RDEPENDS_eina += "efl-data"

#RDEPENDS of eina-examples (eina-examples)
RDEPENDS_eina-examples += "eina"

#RDEPENDS of eo-examples (eo-examples)
RDEPENDS_eo-examples += "eo"

#RDEPENDS of eet-dev (eet-dev)
RDEPENDS_eet-dev += "eet"

#RDEPENDS of eeze-dev (eeze-dev)
RDEPENDS_eeze-dev += "eeze"

#RDEPENDS of efreet-dev (efreet-dev)
RDEPENDS_efreet-dev += "efreet"

#RDEPENDS of ecore-dev (ecore-dev)
RDEPENDS_ecore-dev += "ecore"

#RDEPENDS of ethumb-examples (ethumb-examples)
RDEPENDS_ethumb-examples += "ethumb"

#RDEPENDS of ethumb (ethumb)
RDEPENDS_ethumb += "efl-data"

#RDEPENDS of evas-dev (evas-dev)
RDEPENDS_evas-dev += "evas"

#RDEPENDS of evas (evas)
RDEPENDS_evas += "efl-data"

#RDEPENDS of eeze (eeze)
RDEPENDS_eeze += "efl-data"

#RDEPENDS of ethumb-dev (ethumb-dev)
RDEPENDS_ethumb-dev += "ethumb"

#RDEPENDS of efreet (efreet)
RDEPENDS_efreet += "efl-data"

#RDEPENDS of eldbus-dev (eldbus-dev)
RDEPENDS_eldbus-dev += "eldbus"

#RDEPENDS of eet-examples (eet-examples)
RDEPENDS_eet-examples += "eet"

#RDEPENDS of embryo-dev (embryo-dev)
RDEPENDS_embryo-dev += "embryo"

#RDEPENDS of eio-dev (eio-dev)
RDEPENDS_eio-dev += "eio"

#RDEPENDS of ecore-examples (ecore-examples)
RDEPENDS_ecore-examples += "ecore"

#RDEPENDS of emotion (emotion)
RDEPENDS_emotion += "efl-data"

#RDEPENDS of eldbus-examples (eldbus-examples)
RDEPENDS_eldbus-examples += "eldbus"

#RDEPENDS of eo-dev (eo-dev)
RDEPENDS_eo-dev += "eo"

#RDEPENDS of embryo (embryo)
RDEPENDS_embryo += "efl-data"

#RDEPENDS of eio-examples (eio-examples)
RDEPENDS_eio-examples += "eio"

#RDEPENDS of eet-tools (eet-tools)
RDEPENDS_eet-tools += "eet"

#RDEPENDS of edje-dev (edje-dev)
RDEPENDS_edje-dev += "edje-tools"

#RDEPENDS of edje-tools (edje-tools)
RDEPENDS_edje-tools += "edje"

#RDEPENDS of eet (eet)
RDEPENDS_eet += "efl-data"

#RDEPENDS of eina-dev (eina-dev)
RDEPENDS_eina-dev += "eina"

#RDEPENDS of evas-examples (evas-examples)
RDEPENDS_evas-examples += "evas"

#RDEPENDS of emotion-examples (emotion-examples)
RDEPENDS_emotion-examples += "emotion"

#RDEPENDS of ecore (ecore)
RDEPENDS_ecore += "efl-data"

#RDEPENDS of eldbus (eldbus)
RDEPENDS_eldbus += "efl-data"

#RDEPENDS of edje-examples (edje-examples)
RDEPENDS_edje-examples += "edje"

#RDEPENDS of eio (eio)
RDEPENDS_eio += "efl-data"


DEPENDS = ""
#DEPENDS of efl
DEPENDS += "tiff"
DEPENDS += "ibus"
DEPENDS += "harfbuzz"
DEPENDS += "openssl"
DEPENDS += "curl"
DEPENDS += "fontconfig"
DEPENDS += "systemd"
DEPENDS += "freetype"
DEPENDS += "wayland"
DEPENDS += "gstreamer1.0-plugins-base"
inherit pkgconfig
DEPENDS += "dlog"
DEPENDS += "glib-2.0"
DEPENDS += "lua"
DEPENDS += "libtbm"
DEPENDS += "libbullet"
DEPENDS += "libpng"
DEPENDS += "pixman"
DEPENDS += "libsndfile1"
DEPENDS += "libcheck"
DEPENDS += "giflib"
DEPENDS += "udev"
DEPENDS += "capi-system-sensor"
DEPENDS += "gnutls"
DEPENDS += "util-linux"
DEPENDS += "vconf"
#Replace "DEPENDS" on gettext by "inherit gettext"
inherit gettext
DEPENDS += "virtual/egl"
DEPENDS += "libxkbcommon"
DEPENDS += "fribidi"
DEPENDS += "libjpeg-turbo"
DEPENDS += "dbus"
DEPENDS += "zlib"
DEPENDS += "pulseaudio"
DEPENDS += "libexif"
DEPENDS_append_class-native = " fdupes-native"
DEPENDS_append_class-target = " fdupes-native"
DEPENDS += "gstreamer1.0"

do_prep() {
 cd ${S}
 chmod -Rf a+rX,u+w,g-w,o-w ${S}
 #setup -q
 cp ${S}/packaging/efl.manifest .
 
 
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
  
  CFLAGS="${CFLAGS} -DMESA_EGL_NO_X11_HEADERS "
  
  
  autotools_do_configure
  
  oe_runmake ${PARALLEL_MAKE}
  
  
  
}
EXTRA_OECONF += " --enable-tizen --enable-g-main-loop --disable-xim --disable-scim --disable-gesture --with-tests=regular --enable-wayland --enable-egl --with-opengl=es --enable-tile-rotate --disable-rpath --with-x11=none --enable-tile-rotate --disable-rpath --enable-always-build-examples --enable-systemd --enable-lua-old --enable-i-really-know-what-i-am-doing-and-that-this-will-probably-break-things-and-i-will-fix-them-myself-and-send-patches-aaa"

do_install() {
 export RPM_BUILD_ROOT=${D}
 cd ${S}
 LANG=C
 export LANG
 unset DISPLAY
 rm -rf ${D}
 mkdir -p ${D}
 
 
   oe_runmake \
         DESTDIR=${D} \
         INSTALL_ROOT=${D} \
         BINDIR=${prefix}/bin \
   install  
   rm -f ${D}${infodir}/dir 
   find ${D} -regex ".*\.la$" | xargs rm -f -- 
   find ${D} -regex ".*\.a$" | xargs rm -f --
 oe_runmake datadir=${D}${prefix}/share install-examples
 rm -rf ${D}${prefix}/lib/ecore/system/upower
 
 #find_lang efl
 #fdupes ${D}
 
 
 
}

pkg_postinst_eo() {
    #!/bin/sh -e

    [ "x$D" == "x" ] && ldconfig
}

pkg_postinst_eldbus() {
    #!/bin/sh -e

    [ "x$D" == "x" ] && ldconfig
}

pkg_postinst_efreet() {
    #!/bin/sh -e

    [ "x$D" == "x" ] && ldconfig
}

pkg_postinst_embryo() {
    #!/bin/sh -e

    [ "x$D" == "x" ] && ldconfig
}

pkg_postinst_evas() {
    #!/bin/sh -e

    [ "x$D" == "x" ] && ldconfig
}

pkg_postinst_eet() {
    #!/bin/sh -e

    [ "x$D" == "x" ] && ldconfig
}

pkg_postinst_ephysics() {
    #!/bin/sh -e

    [ "x$D" == "x" ] && ldconfig
}

pkg_postinst_emotion() {
    #!/bin/sh -e

    [ "x$D" == "x" ] && ldconfig
}

pkg_postinst_eio() {
    #!/bin/sh -e

    [ "x$D" == "x" ] && ldconfig
}

pkg_postinst_ecore() {
    #!/bin/sh -e

    [ "x$D" == "x" ] && ldconfig
    f="/etc/profile.d/ecore.sh"
    grep --silent EFL_WAYLAND_USE_XDG_SHELL "$f" \
        || printf "\nEFL_WAYLAND_USE_XDG_SHELL='defined'\nexport EFL_WAYLAND_USE_XDG_SHELL\n" >> "$f"
    grep --silent ECORE_EVAS_ENGINE "$f" \
        || printf "\nECORE_EVAS_ENGINE=wayland_shm\n[ ! -d /dev/dri ] || ECORE_EVAS_ENGINE=wayland_egl\nexport ECORE_EVAS_ENGINE" >> "$f"
    grep --silent ECORE_IMF_MODULE "$f" \
        || printf "\nECORE_IMF_MODULE=wayland\nexport ECORE_IMF_MODULE\n" >> "$f"

}

pkg_postinst_edje() {
    #!/bin/sh -e

    [ "x$D" == "x" ] && ldconfig
}

pkg_postinst_eina() {
    #!/bin/sh -e

    [ "x$D" == "x" ] && ldconfig
}

pkg_postinst_ethumb() {
    #!/bin/sh -e

    [ "x$D" == "x" ] && ldconfig
}

pkg_postinst_eeze() {
    #!/bin/sh -e

    [ "x$D" == "x" ] && ldconfig
}

pkg_postrm_efreet() {
    #!/bin/sh -e

    [ "x$D" == "x" ] && ldconfig
}

pkg_postrm_eo() {
    #!/bin/sh -e

    [ "x$D" == "x" ] && ldconfig
}

pkg_postrm_eina() {
    #!/bin/sh -e

    [ "x$D" == "x" ] && ldconfig
}

pkg_postrm_eet() {
    #!/bin/sh -e

    [ "x$D" == "x" ] && ldconfig
}

pkg_postrm_eio() {
    #!/bin/sh -e

    [ "x$D" == "x" ] && ldconfig
}

pkg_postrm_evas() {
    #!/bin/sh -e

    [ "x$D" == "x" ] && ldconfig
}

pkg_postrm_embryo() {
    #!/bin/sh -e

    [ "x$D" == "x" ] && ldconfig
}

pkg_postrm_emotion() {
    #!/bin/sh -e

    [ "x$D" == "x" ] && ldconfig
}

pkg_postrm_ephysics() {
    #!/bin/sh -e

    [ "x$D" == "x" ] && ldconfig
}

pkg_postrm_ethumb() {
    #!/bin/sh -e

    [ "x$D" == "x" ] && ldconfig
}

pkg_postrm_eeze() {
    #!/bin/sh -e

    [ "x$D" == "x" ] && ldconfig
}

pkg_postrm_eldbus() {
    #!/bin/sh -e

    [ "x$D" == "x" ] && ldconfig
}

pkg_postrm_ecore() {
    #!/bin/sh -e

    [ "x$D" == "x" ] && ldconfig
}

pkg_postrm_edje() {
    #!/bin/sh -e

    [ "x$D" == "x" ] && ldconfig
}

PACKAGES = "${PN}-dbg ${PN}-doc ${PN}-locale"
PACKAGES += " emotion "
PACKAGES += " ephysics-examples "
PACKAGES += " eo "
PACKAGES += " ephysics-dev "
PACKAGES += " edje "
PACKAGES += " emotion-dev "
PACKAGES += " eina "
PACKAGES += " eina-examples "
PACKAGES += " eo-examples "
PACKAGES += " eet-dev "
PACKAGES += " ephysics "
PACKAGES += " eeze-dev "
PACKAGES += " efreet-dev "
PACKAGES += " ecore-dev "
PACKAGES += " eina-dev "
PACKAGES += " ethumb "
PACKAGES += " evas-dev "
PACKAGES += " efl-data "
PACKAGES += " evas "
PACKAGES += " eeze "
PACKAGES += " ethumb-dev "
PACKAGES += " efreet "
PACKAGES += " eldbus-dev "
PACKAGES += " eet-examples "
PACKAGES += " embryo-dev "
PACKAGES += " ethumb-examples "
PACKAGES += " eio-dev "
PACKAGES += " ecore-examples "
PACKAGES += " ecore "
PACKAGES += " eldbus-examples "
PACKAGES += " eo-dev "
PACKAGES += " embryo "
PACKAGES += " eio-examples "
PACKAGES += " eet-tools "
PACKAGES += " edje-dev "
PACKAGES += " edje-tools "
PACKAGES += " eet "
PACKAGES += " evas-examples "
PACKAGES += " emotion-examples "
PACKAGES += " eldbus "
PACKAGES += " edje-examples "
PACKAGES += " eio "

emotion_files = ""
emotion_files += "${prefix}/lib/libemotion.so.*"
emotion_files += "${prefix}/lib/edje/modules/emotion/*/module.so"
emotion_files += "${prefix}/lib/emotion/modules/*/*/module.so"
emotion_files += "${prefix}/share/emotion/*"
emotion_files += "${prefix}/bin/emotion_test"
MANIFESTFILES_emotion = "efl.manifest"

ephysics-examples_files = ""
ephysics-examples_files += "${prefix}/share/ephysics/examples/*"

eo_files = ""
eo_files += "${prefix}/lib/libeo.so.*"
MANIFESTFILES_eo = "efl.manifest"

ephysics-dev_files = ""
ephysics-dev_files += "${prefix}/lib/libephysics.so"
ephysics-dev_files += "${prefix}/lib/pkgconfig/ephysics.pc"
ephysics-dev_files += "${prefix}/include/ephysics-1/EPhysics.h"

edje_files = ""
edje_files += "${prefix}/lib/libedje.so.*"
edje_files += "${prefix}/lib/edje/utils/*/*"
edje_files += "${prefix}/share/edje/include/edje.inc"
edje_files += "${prefix}/share/mime/packages/edje.xml"
MANIFESTFILES_edje = "efl.manifest"

emotion-dev_files = ""
emotion-dev_files += "${prefix}/include/emotion-1/*"
emotion-dev_files += "${prefix}/lib/libemotion.so"
emotion-dev_files += "${prefix}/lib/pkgconfig/emotion*.pc"
emotion-dev_files += "${prefix}/lib/cmake/Emotion/*.cmake"
MANIFESTFILES_emotion-dev = "efl.manifest"

eina_files = ""
eina_files += "${prefix}/lib/libeina.so.*"
eina_files += "${prefix}/bin/eina-bench-cmp"
MANIFESTFILES_eina = "efl.manifest"

eina-examples_files = ""
eina-examples_files += "${prefix}/share/eina/examples/*"
eina-examples_files += "${prefix}/lib/eina/examples/*"
MANIFESTFILES_eina-examples = "efl.manifest"

eo-examples_files = ""
eo-examples_files += "${prefix}/share/eo/examples/*"
eo-examples_files += "${prefix}/lib/eo/examples/*"
MANIFESTFILES_eo-examples = "efl.manifest"

eet-dev_files = ""
eet-dev_files += "${prefix}/include/eet-1/*.h"
eet-dev_files += "${prefix}/lib/libeet.so"
eet-dev_files += "${prefix}/lib/pkgconfig/eet*.pc"
eet-dev_files += "${prefix}/lib/cmake/Eet/*.cmake"
MANIFESTFILES_eet-dev = "efl.manifest"

ephysics_files = ""
ephysics_files += "${prefix}/lib/libephysics.so.*"

eeze-dev_files = ""
eeze-dev_files += "${prefix}/include/eeze-1/*.h"
eeze-dev_files += "${prefix}/lib/libeeze.so"
eeze-dev_files += "${prefix}/lib/pkgconfig/eeze*.pc"
eeze-dev_files += "${prefix}/lib/cmake/Eeze/*.cmake"
MANIFESTFILES_eeze-dev = "efl.manifest"

efreet-dev_files = ""
efreet-dev_files += "${prefix}/include/efreet-1/*.h"
efreet-dev_files += "${prefix}/lib/libefreet.so"
efreet-dev_files += "${prefix}/lib/libefreet_mime.so"
efreet-dev_files += "${prefix}/lib/libefreet_trash.so"
efreet-dev_files += "${prefix}/lib/pkgconfig/efreet*.pc"
efreet-dev_files += "${prefix}/lib/cmake/Efreet/*.cmake"
MANIFESTFILES_efreet-dev = "efl.manifest"

ecore-dev_files = ""
ecore-dev_files += "${prefix}/include/ecore*/*.h"
ecore-dev_files += "${prefix}/lib/libecore.so"
ecore-dev_files += "${prefix}/lib/libecore_audio.so"
ecore-dev_files += "${prefix}/lib/libecore_avahi.so"
ecore-dev_files += "${prefix}/lib/libecore_con.so"
ecore-dev_files += "${prefix}/lib/libecore_evas.so"
ecore-dev_files += "${prefix}/lib/libecore_file.so"
ecore-dev_files += "${prefix}/lib/libecore_imf.so"
ecore-dev_files += "${prefix}/lib/libecore_imf_evas.so"
ecore-dev_files += "${prefix}/lib/libecore_input.so"
ecore-dev_files += "${prefix}/lib/libecore_input_evas.so"
ecore-dev_files += "${prefix}/lib/libecore_ipc.so"
ecore-dev_files += "${prefix}/lib/libecore_wayland.so"
ecore-dev_files += "${prefix}/lib/pkgconfig/ecore*.pc"
ecore-dev_files += "${prefix}/lib/cmake/Ecore/*.cmake"
MANIFESTFILES_ecore-dev = "efl.manifest"

eina-dev_files = ""
eina-dev_files += "${prefix}/include/eina-1/*.h"
eina-dev_files += "${prefix}/include/eina-1/eina/*"
eina-dev_files += "${prefix}/lib/libeina.so"
eina-dev_files += "${prefix}/lib/pkgconfig/eina*.pc"
eina-dev_files += "${prefix}/lib/cmake/Eina/*.cmake"
MANIFESTFILES_eina-dev = "efl.manifest"

ethumb_files = ""
ethumb_files += "${prefix}/lib/libethumb.so.*"
ethumb_files += "${prefix}/lib/libethumb_client.so.*"
ethumb_files += "${prefix}/share/dbus-1/services/org.enlightenment.Ethumb.service"
ethumb_files += "${prefix}/share/ethumb/*"
ethumb_files += "${prefix}/share/ethumb_client/*"
ethumb_files += "${prefix}/lib/ethumb/modules/*/*/module.so"
ethumb_files += "${prefix}/lib/ethumb/modules/*/*/template.edj"
ethumb_files += "${prefix}/lib/ethumb_client/utils/*/ethumbd_slave"
ethumb_files += "${prefix}/bin/ethumb"
ethumb_files += "${prefix}/bin/ethumbd"
ethumb_files += "${prefix}/bin/ethumbd_client"
MANIFESTFILES_ethumb = "efl.manifest"

evas-dev_files = ""
evas-dev_files += "${prefix}/include/evas-1/*.h"
evas-dev_files += "${prefix}/lib/libevas.so"
evas-dev_files += "${prefix}/lib/pkgconfig/evas*.pc"
evas-dev_files += "${prefix}/lib/cmake/Evas/*.cmake"
MANIFESTFILES_evas-dev = "efl.manifest"

efl-data_files = ""
efl-data_files += "${prefix}/include/efl-1/Efl_Config.h"
MANIFESTFILES_${PN}-data = "efl.manifest"

evas_files = ""
evas_files += "${prefix}/bin/evas_cserve2_client"
evas_files += "${prefix}/bin/evas_cserve2_debug"
evas_files += "${prefix}/bin/evas_cserve2_shm_debug"
evas_files += "${prefix}/bin/evas_cserve2_usage"
evas_files += "${prefix}/lib/evas/modules/*/*/*/module.so"
evas_files += "${prefix}/lib/libevas.so.*"
evas_files += "${prefix}/lib/evas/cserve2"
evas_files += "${prefix}/share/evas/checkme"
MANIFESTFILES_evas = "efl.manifest"

eeze_files = ""
eeze_files += "${prefix}/lib/libeeze.so.*"
eeze_files += "${prefix}/bin/eeze_disk_ls"
eeze_files += "${prefix}/bin/eeze_mount"
eeze_files += "${prefix}/bin/eeze_scanner"
eeze_files += "${prefix}/bin/eeze_umount"
eeze_files += "${prefix}/lib/eeze/modules/sensor/*/*/module.so"
eeze_files += "${prefix}/share/eeze/checkme"
MANIFESTFILES_eeze = "efl.manifest"

ethumb-dev_files = ""
ethumb-dev_files += "${prefix}/include/ethumb-1/*.h"
ethumb-dev_files += "${prefix}/include/ethumb-client-1/*.h"
ethumb-dev_files += "${prefix}/lib/libethumb.so"
ethumb-dev_files += "${prefix}/lib/libethumb_client.so"
ethumb-dev_files += "${prefix}/lib/pkgconfig/ethumb*.pc"
ethumb-dev_files += "${prefix}/lib/cmake/Ethumb/*.cmake"
ethumb-dev_files += "${prefix}/lib/cmake/EthumbClient/*.cmake"
MANIFESTFILES_ethumb-dev = "efl.manifest"

efreet_files = ""
efreet_files += "${prefix}/share/dbus-1/services/org.enlightenment.Efreet.service"
efreet_files += "${prefix}/bin/efreetd"
efreet_files += "${prefix}/lib/efreet/*/efreet_desktop_cache_create"
efreet_files += "${prefix}/lib/efreet/*/efreet_icon_cache_create"
efreet_files += "${prefix}/lib/libefreet.so.*"
efreet_files += "${prefix}/lib/libefreet_mime.so.*"
efreet_files += "${prefix}/lib/libefreet_trash.so.*"
efreet_files += "${prefix}/share/efreet/*"
MANIFESTFILES_efreet = "efl.manifest"

eldbus-dev_files = ""
eldbus-dev_files += "${prefix}/lib/libeldbus.so"
eldbus-dev_files += "${prefix}/lib/pkgconfig/eldbus*.pc"
eldbus-dev_files += "${prefix}/include/eldbus*/*"
eldbus-dev_files += "${prefix}/lib/cmake/Eldbus/*.cmake"
MANIFESTFILES_eldbus-dev = "efl.manifest"

eet-examples_files = ""
eet-examples_files += "${prefix}/share/eet/examples/*"
eet-examples_files += "${prefix}/lib/eet/examples/*"
MANIFESTFILES_eet-examples = "efl.manifest"

embryo-dev_files = ""
embryo-dev_files += "${prefix}/include/embryo-1/*.h"
embryo-dev_files += "${prefix}/lib/libembryo.so"
embryo-dev_files += "${prefix}/lib/pkgconfig/embryo*.pc"
MANIFESTFILES_embryo-dev = "efl.manifest"

ethumb-examples_files = ""
ethumb-examples_files += "${prefix}/share/ethumb_client/examples/*"
ethumb-examples_files += "${prefix}/lib/ethumb_client/examples/*"
MANIFESTFILES_ethumb-examples = "efl.manifest"

eio-dev_files = ""
eio-dev_files += "${prefix}/include/eio-1/*"
eio-dev_files += "${prefix}/lib/libeio.so"
eio-dev_files += "${prefix}/lib/pkgconfig/eio*.pc"
MANIFESTFILES_eio-dev = "efl.manifest"

ecore-examples_files = ""
ecore-examples_files += "${prefix}/share/ecore*/examples/*"
ecore-examples_files += "${prefix}/lib/ecore*/examples/*"
MANIFESTFILES_ecore-examples = "efl.manifest"

ecore_files = ""
ecore_files += "${prefix}/lib/libecore.so.*"
ecore_files += "${prefix}/lib/libecore_avahi.so.*"
ecore_files += "${prefix}/lib/libecore_audio.so.*"
ecore_files += "${prefix}/lib/libecore_avahi.so.*"
ecore_files += "${prefix}/lib/libecore_con.so.*"
ecore_files += "${prefix}/lib/libecore_evas.so.*"
ecore_files += "${prefix}/lib/libecore_file.so.*"
ecore_files += "${prefix}/lib/libecore_imf.so.*"
ecore_files += "${prefix}/lib/libecore_imf_evas.so.*"
ecore_files += "${prefix}/lib/libecore_input.so.*"
ecore_files += "${prefix}/lib/libecore_input_evas.so.*"
ecore_files += "${prefix}/lib/libecore_ipc.so.*"
ecore_files += "${prefix}/lib/libecore_wayland.so.*"
ecore_files += "${prefix}/lib/ecore_evas/engines/*/*/module.so"
ecore_files += "${prefix}/lib/ecore_imf/modules/*/*/module.so"
ecore_files += "${prefix}/lib/ecore/system/tizen/*/module.so"
ecore_files += "${prefix}/lib/ecore/system/systemd/v-*/module.so"
ecore_files += "${prefix}/share/ecore/checkme"
ecore_files += "${prefix}/share/ecore_imf/checkme"
MANIFESTFILES_ecore = "efl.manifest"

eldbus-examples_files = ""
eldbus-examples_files += "${prefix}/share/eldbus/examples/*"
eldbus-examples_files += "${prefix}/lib/eldbus/examples/*"
MANIFESTFILES_eldbus-examples = "efl.manifest"

eo-dev_files = ""
eo-dev_files += "${prefix}/include/eo-1/*.h"
eo-dev_files += "${prefix}/lib/libeo.so"
eo-dev_files += "${prefix}/lib/pkgconfig/eo*.pc"
eo-dev_files += "${prefix}/share/eo/gdb/eo_gdb.py"
eo-dev_files += "${prefix}/share/gdb/auto-load/usr/lib*/*"
eo-dev_files += "${prefix}/lib/cmake/Eo/*.cmake"
MANIFESTFILES_eo-dev = "efl.manifest"

embryo_files = ""
embryo_files += "${prefix}/bin/embryo_cc"
embryo_files += "${prefix}/lib/libembryo.so.*"
embryo_files += "${prefix}/share/embryo/include/default.inc"
MANIFESTFILES_embryo = "efl.manifest"

eio-examples_files = ""
eio-examples_files += "${prefix}/share/eio/examples/*"
eio-examples_files += "${prefix}/lib/eio/examples/*"
MANIFESTFILES_eio-examples = "efl.manifest"

eet-tools_files = ""
eet-tools_files += "${prefix}/bin/eet"
MANIFESTFILES_eet-tools = "efl.manifest"

edje-dev_files = ""
edje-dev_files += "${prefix}/include/edje-1/*.h"
edje-dev_files += "${prefix}/lib/libedje.so"
edje-dev_files += "${prefix}/lib/pkgconfig/edje*.pc"
edje-dev_files += "${prefix}/lib/cmake/Edje/*.cmake"
MANIFESTFILES_edje-dev = "efl.manifest"

edje-tools_files = ""
edje-tools_files += "${prefix}/bin/edje*"
edje-tools_files += "${prefix}/share/edje/data/*"
MANIFESTFILES_edje-tools = "efl.manifest"

eet_files = ""
eet_files += "${prefix}/lib/libeet*.so.*"
MANIFESTFILES_eet = "efl.manifest"

evas-examples_files = ""
evas-examples_files += "${prefix}/share/evas/examples/*"
evas-examples_files += "${prefix}/lib/evas/examples/*"
MANIFESTFILES_evas-examples = "efl.manifest"

emotion-examples_files = ""
emotion-examples_files += "${prefix}/share/emotion/examples/*"
emotion-examples_files += "${prefix}/lib/emotion/examples/*"
MANIFESTFILES_emotion-examples = "efl.manifest"

eldbus_files = ""
eldbus_files += "${prefix}/lib/libeldbus.so.*"
eldbus_files += "${prefix}/bin/eldbus*"
MANIFESTFILES_eldbus = "efl.manifest"

edje-examples_files = ""
edje-examples_files += "${prefix}/share/edje/examples/*"
edje-examples_files += "${prefix}/lib/edje/examples/*"
MANIFESTFILES_edje-examples = "efl.manifest"

eio_files = ""
eio_files += "${prefix}/lib/libeio.so.*"
MANIFESTFILES_eio = "efl.manifest"

FILES_emotion = "${emotion_files}"
FILES_ephysics-examples = "${ephysics-examples_files}"
FILES_eo = "${eo_files}"
FILES_ephysics-dev = "${ephysics-dev_files}"
FILES_edje = "${edje_files}"
FILES_emotion-dev = "${emotion-dev_files}"
FILES_eina = "${eina_files}"
FILES_eina-examples = "${eina-examples_files}"
FILES_eo-examples = "${eo-examples_files}"
FILES_eet-dev = "${eet-dev_files}"
FILES_ephysics = "${ephysics_files}"
FILES_eeze-dev = "${eeze-dev_files}"
FILES_efreet-dev = "${efreet-dev_files}"
FILES_ecore-dev = "${ecore-dev_files}"
FILES_eina-dev = "${eina-dev_files}"
FILES_ethumb = "${ethumb_files}"
FILES_evas-dev = "${evas-dev_files}"
FILES_${PN}-data = "${efl-data_files}"
FILES_evas = "${evas_files}"
FILES_eeze = "${eeze_files}"
FILES_ethumb-dev = "${ethumb-dev_files}"
FILES_efreet = "${efreet_files}"
FILES_eldbus-dev = "${eldbus-dev_files}"
FILES_eet-examples = "${eet-examples_files}"
FILES_embryo-dev = "${embryo-dev_files}"
FILES_ethumb-examples = "${ethumb-examples_files}"
FILES_eio-dev = "${eio-dev_files}"
FILES_ecore-examples = "${ecore-examples_files}"
FILES_ecore = "${ecore_files}"
FILES_eldbus-examples = "${eldbus-examples_files}"
FILES_eo-dev = "${eo-dev_files}"
FILES_embryo = "${embryo_files}"
FILES_eio-examples = "${eio-examples_files}"
FILES_eet-tools = "${eet-tools_files}"
FILES_edje-dev = "${edje-dev_files}"
FILES_edje-tools = "${edje-tools_files}"
FILES_eet = "${eet_files}"
FILES_evas-examples = "${evas-examples_files}"
FILES_emotion-examples = "${emotion-examples_files}"
FILES_eldbus = "${eldbus_files}"
FILES_edje-examples = "${edje-examples_files}"
FILES_eio = "${eio_files}"

PKG_emotion= "emotion"
PKG_ephysics-examples= "ephysics-examples"
PKG_eo= "eo"
PKG_ephysics-dev= "ephysics-dev"
PKG_edje= "edje"
PKG_emotion-dev= "emotion-dev"
PKG_eina= "eina"
PKG_eina-examples= "eina-examples"
PKG_eo-examples= "eo-examples"
PKG_eet-dev= "eet-dev"
PKG_ephysics= "ephysics"
PKG_eeze-dev= "eeze-dev"
PKG_efreet-dev= "efreet-dev"
PKG_ecore-dev= "ecore-dev"
PKG_eina-dev= "eina-dev"
PKG_ethumb= "ethumb"
PKG_evas-dev= "evas-dev"
PKG_efl-data= "efl-data"
PKG_evas= "evas"
PKG_eeze= "eeze"
PKG_ethumb-dev= "ethumb-dev"
PKG_efreet= "efreet"
PKG_eldbus-dev= "eldbus-dev"
PKG_eet-examples= "eet-examples"
PKG_embryo-dev= "embryo-dev"
PKG_ethumb-examples= "ethumb-examples"
PKG_eio-dev= "eio-dev"
PKG_ecore-examples= "ecore-examples"
PKG_ecore= "ecore"
PKG_eldbus-examples= "eldbus-examples"
PKG_eo-dev= "eo-dev"
PKG_embryo= "embryo"
PKG_eio-examples= "eio-examples"
PKG_eet-tools= "eet-tools"
PKG_edje-dev= "edje-dev"
PKG_edje-tools= "edje-tools"
PKG_eet= "eet"
PKG_evas-examples= "evas-examples"
PKG_emotion-examples= "emotion-examples"
PKG_eldbus= "eldbus"
PKG_edje-examples= "edje-examples"
PKG_eio= "eio"

require efl-extraconf.inc

