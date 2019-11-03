#!/bin/sh

VERSION="3.1.1"
QEMU_URL="http://download.qemu-project.org/qemu-${VERSION}.tar.xz"
QEMU_SHA384="28ff22ec4b8c957309460aa55d0b3188e971be1ea7dfebfb2ecc7903cd20cfebc2a7c97eedfcc7595f708357f1623f8b"

echo "========================"
echo "QEMU SanCov build script"
echo "========================"
echo

echo "[*] Performing basic sanity checks..."

if [ ! "`uname -s`" = "Linux" ]; then

  echo "[-] Error: QEMU instrumentation is supported only on Linux."
  exit 1

fi

if [ ! -f "patches/qemu-sancov-common.h" ]; then

  echo "[-] Error: key files not found - wrong working directory?"
  exit 1

fi

for i in libtool wget python automake autoconf sha384sum bison iconv; do

  T=`which "$i" 2>/dev/null`

  if [ "$T" = "" ]; then

    echo "[-] Error: '$i' not found, please install first."
    exit 1

  fi

done

if [ ! -d "/usr/include/glib-2.0/" -a ! -d "/usr/local/include/glib-2.0/" ]; then

  echo "[-] Error: devel version of 'glib2' not found, please install first."
  exit 1

fi

echo "[+] All checks passed!"

ARCHIVE="`basename -- "$QEMU_URL"`"

CKSUM=`sha384sum -- "$ARCHIVE" 2>/dev/null | cut -d' ' -f1`

if [ ! "$CKSUM" = "$QEMU_SHA384" ]; then

  echo "[*] Downloading QEMU ${VERSION} from the web..."
  rm -f "$ARCHIVE"
  wget -O "$ARCHIVE" -- "$QEMU_URL" || exit 1

  CKSUM=`sha384sum -- "$ARCHIVE" 2>/dev/null | cut -d' ' -f1`

fi

if [ "$CKSUM" = "$QEMU_SHA384" ]; then

  echo "[+] Cryptographic signature on $ARCHIVE checks out."

else

  echo "[-] Error: signature mismatch on $ARCHIVE (perhaps download error?), removing archive ..."
  rm -f "$ARCHIVE"
  exit 1

fi

echo "[*] Uncompressing archive (this will take a while)..."

rm -rf "qemu-${VERSION}" || exit 1
tar xf "$ARCHIVE" || exit 1

echo "[+] Unpacking successful."

if [ -n "$HOST" ]; then
  echo "[+] Configuring host architecture to $HOST..."
  CROSS_PREFIX=$HOST-
else
  CROSS_PREFIX=
fi

echo "[*] Configuring QEMU for $CPU_TARGET..."

ORIG_CPU_TARGET="$CPU_TARGET"

test "$CPU_TARGET" = "" && CPU_TARGET="`uname -m`"
test "$CPU_TARGET" = "i686" && CPU_TARGET="i386"

cd qemu-$VERSION || exit 1

echo "[*] Applying patches..."

patch -p1 <../patches/elfload.diff || exit 1
patch -p1 <../patches/cpu-exec.diff || exit 1
patch -p1 <../patches/translate-all.diff || exit 1
patch -p1 <../patches/tcg.diff || exit 1
patch -p1 <../patches/i386-translate.diff || exit 1

echo "[+] Patching done."

if [ "$STATIC" = "1" ]; then

  CFLAGS="-O3 -ggdb -Wl,--no-as-needed -ldl" ./configure \
    --extra-ldflags=-ldl --disable-bsd-user --disable-guest-agent --disable-strip --disable-werror \
	  --disable-gcrypt --disable-debug-info --disable-debug-tcg --enable-docs --disable-tcg-interpreter \
	  --enable-attr --disable-brlapi --disable-linux-aio --disable-bzip2 --disable-bluez --disable-cap-ng \
	  --disable-curl --disable-fdt --disable-glusterfs --disable-gnutls --disable-nettle --disable-gtk \
	  --disable-rdma --disable-libiscsi --disable-vnc-jpeg --enable-kvm --disable-lzo --disable-curses \
	  --disable-libnfs --disable-numa --disable-opengl --disable-vnc-png --disable-rbd --disable-vnc-sasl \
	  --disable-sdl --disable-seccomp --disable-smartcard --disable-snappy --disable-spice --disable-libssh2 \
	  --disable-libusb --disable-usb-redir --disable-vde --disable-vhost-net --disable-virglrenderer \
	  --disable-virtfs --disable-vnc --disable-vte --disable-xen --disable-xen-pci-passthrough --disable-xfsctl \
	  --enable-linux-user --disable-system --disable-blobs --disable-tools \
	  --target-list="${CPU_TARGET}-linux-user" --static --disable-pie --cross-prefix=$CROSS_PREFIX || exit 1

else

  # --enable-pie seems to give a couple of exec's a second performance
  # improvement, much to my surprise. Not sure how universal this is..
  
  CFLAGS="-O3 -ggdb -Wl,--no-as-needed -ldl" ./configure --disable-system \
    --enable-linux-user --disable-gtk --disable-sdl --disable-vnc \
    --target-list="${CPU_TARGET}-linux-user" --enable-pie --enable-kvm \
    --extra-ldflags=-ldl $CROSS_PREFIX || exit 1

fi

echo "[+] Configuration complete."

echo "[*] Attempting to build QEMU (fingers crossed!)..."

make -j `nproc` || exit 1

echo "[+] Build process successful!"

echo "[*] Copying binary..."

cp -f "${CPU_TARGET}-linux-user/qemu-${CPU_TARGET}" "../qemu-sancov-${CPU_TARGET}" || exit 1

cd ..
ls -l "qemu-sancov-${CPU_TARGET}" || exit 1

echo "[+] Successfully created qemu-sancov-${CPU_TARGET}."

exit 0
