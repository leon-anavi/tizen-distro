DESCRIPTION = "Ofono EFL Dialer"
HOMEPAGE = "http://nohomepage.org"
SECTION = "Applications/Telephony"
LICENSE = "Apache-2.0"
PV = "0.1.7"

SRC_URI = ""

S = "${WORKDIR}/git"

inherit manifest autotools-brokensep

BBCLASSEXTEND = ""
PROVIDES = ""

#PROVIDES by lemolo


RDEPENDS = ""
#RDEPENDS of lemolo (${PN})
RDEPENDS_${PN} += "automotive-message-broker"
RDEPENDS_${PN} += "ofono"


DEPENDS = ""
#DEPENDS of lemolo
#Replace "DEPENDS" on gettext by "inherit gettext"
inherit gettext
DEPENDS += "pulseaudio"
DEPENDS += "ofono"
DEPENDS += "capi-system-power"
DEPENDS += "evas"
DEPENDS += "app-svc"
inherit pkgconfig
DEPENDS += "app-core"
DEPENDS += "contacts-service"
DEPENDS += "aul"
DEPENDS += "efl"
DEPENDS += "notification"
DEPENDS += "elementary"
DEPENDS += "ecore"
DEPENDS += "eldbus"
DEPENDS += "vconf"

do_prep() {
 cd ${S}
 chmod -Rf a+rX,u+w,g-w,o-w ${S}
 #setup -q -n lemolo-0.1.7
 
 
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
  
  
  
   
  autotools_do_configure
  
  oe_runmake ${PARALLEL_MAKE}
  
  
  
}
EXTRA_OECONF += " --enable-notification --enable-tizen"

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
 #find_lang lemolo
 
 
}

PACKAGES = "${PN}-dbg ${PN}-doc ${PN}-locale"
PACKAGES += " lemolo "

lemolo_files = ""
lemolo_files += "${prefix}/bin/answer_daemon"
lemolo_files += "${prefix}/bin/dialer"
lemolo_files += "${prefix}/bin/messages"
lemolo_files += "${prefix}/bin/dialer_daemon"
lemolo_files += "${prefix}/bin/dialer_open"
lemolo_files += "${prefix}/bin/message_daemon"
lemolo_files += "${prefix}/share/lemolo/examples/contacts.csv"
lemolo_files += "${prefix}/share/lemolo/ringtones/default.wav"
lemolo_files += "${prefix}/share/lemolo/scripts/ofono-efl-contacts-db-create.py"
lemolo_files += "${prefix}/share/lemolo/themes/default.edj"
lemolo_files += "${prefix}/share/lemolo/themes/night.edj"
lemolo_files += "${prefix}/share/lemolo/tizen-examples/order"
lemolo_files += "${prefix}/share/packages/org.tizen.dialer.xml"
lemolo_files += "${prefix}/share/icons/default/small/org.tizen.dialer.png"
lemolo_files += "${prefix}/share/dbus-1/services/org.tizen.dialer.service"

FILES_${PN} = "${lemolo_files}"

PKG_lemolo= "lemolo"

require lemolo-extraconf.inc

