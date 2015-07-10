# Maintainer: Milan Oberkirch <aur@oberkirch.org>
pkgname=pong
pkgver=0.01
pkgrel=0
pkgdesc="Simple pong game."
arch=('any')
url="http://oberkirch.org"
license=('GPL3')
depends=('bash' 'ncurses')
makedepends=('git' 'gtest' 'gcc')
md5sums=()

_gitroot="git@github.com:zvyn/pong.git"
_gitname=pong

build() {
  cd "$srcdir"
  msg "Connecting to GIT server...."

  if [[ -d "$_gitname" ]]; then
    cd "$_gitname" && git pull origin
    msg "The local files are updated."
  else
    git clone "$_gitroot" "$_gitname"
  fi

  msg "GIT checkout done or server timeout"
}

package() {
  mkdir -p "${pkgdir}/usr/bin"
  cd "$srcdir/$_gitname/" &&\
      make &&\
      install pong ${pkgdir}/usr/bin/
}

# vim:set ts=2 sw=2 et:
