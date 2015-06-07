DESCRIPTION = "Python Bindings for libxml2"
HOMEPAGE = "http://xmlsoft.org"
SECTION = "Platform Development/Python"
LICENSE = "MIT"
PV = "2.8.0"

SRC_URI = ""

S = "${WORKDIR}/git"

inherit manifest autotools-brokensep

BBCLASSEXTEND = ""
PROVIDES = ""

#PROVIDES by python-libxml2
# the PROVIDES rules is ignore "libxml2-python = 2.8.0"
PROVIDES += "libxml2-python"
RPROVIDES_python-libxml2 += "libxml2-python"


RDEPENDS = ""
#RDEPENDS of python-libxml2 (${PN})
RDEPENDS_${PN} += "libxml2"


DEPENDS = ""
#DEPENDS of python-libxml2
inherit pythonnative
DEPENDS += "libxml2"
DEPENDS += "python-xml"

do_prep() {
 cd ${S}
 chmod -Rf a+rX,u+w,g-w,o-w ${S}
 #setup -q -n libxml2-2.8.0
 
 
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
  
  export CFLAGS="$CFLAGS -fno-strict-aliasing"
  
  autotools_do_configure
  
  # use libxml2 as built by libxml2 source package
  mkdir .libs
  cp -v ${prefix}/lib/libxml2.la .
  make -C python ${PARALLEL_MAKE}
  
  
  
}
EXTRA_OECONF += " --with-fexceptions --with-history --enable-ipv6 --with-sax1 --with-regexps --with-threads --with-reader --with-http"

do_install() {
 export RPM_BUILD_ROOT=${D}
 cd ${S}
 LANG=C
 export LANG
 unset DISPLAY
 rm -rf ${D}
 mkdir -p ${D}
 
 make -C python install \
     DESTDIR=${D} \
     pythondir=/usr/lib/python2.7/site-packages \
     PYTHON_SITE_PACKAGES=/usr/lib/python2.7/site-packages
 chmod a-x python/tests/*.py
 # Unwanted doc stuff
 rm -fr ${D}${prefix}/share/doc
 rm -f python/tests/Makefile*
 # #223696
 rm -f ${D}/usr/lib/python2.7/site-packages/*.{la,a}
 
 
}

PACKAGES = "${PN}-dbg ${PN}-doc ${PN}-locale"
PACKAGES += " python-libxml2 "

python-libxml2_files = ""
python-libxml2_files += "python/libxml2class.txt"
python-libxml2_files += "python/tests"
python-libxml2_files += "/usr/lib/python2.7/site-packages/*"

FILES_${PN} = "${python-libxml2_files}"

PKG_python-libxml2= "python-libxml2"

require python-libxml2-extraconf.inc

