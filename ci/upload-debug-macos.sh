#!/bin/bash -ex
cd build/Binaries/metaforce-gui.app/Contents/MacOS
for f in hecl metaforce-gui metaforce visigen; do
  dsymutil $f
  strip -S $f
done
sentry-cli upload-dif --org axiodl --project metaforce {hecl,metaforce-gui,metaforce,visigen}{,.dSYM} --include-sources
tar acfv "$GITHUB_WORKSPACE"/debug.tar.xz --options compression-level=3 -- *.dSYM
rm -r -- *.dSYM
