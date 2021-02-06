#!/usr/bin/env bash

set -e

if [ -z "$1" ]; then
    echo "Usage: ./make_app.sh <test_executable> [<.mobileprovision>] [<app_id>]"
    exit 1
fi

MOBILEPROVISION=$2
if [ -z "$2" ]; then
    MOBILEPROVISION=`ls -t ~/Library/MobileDevice/Provisioning\ Profiles/*.mobileprovision | head -1`
fi

TMP=tmp.app
if [ ! -d $TMP ]; then
    mkdir $TMP
fi
TEST=$1
EXECUTABLE_NAME=${TEST##*/}
echo $EXECUTABLE_NAME

cp -v "$MOBILEPROVISION" $TMP/embedded.mobileprovision
cp -v $TEST $TMP/$EXECUTABLE_NAME

PRODUCT_BUNDLE_IDENTIFIER=$3
if [ -z "$PRODUCT_BUNDLE_IDENTIFIER" ]; then
    PRODUCT_BUNDLE_IDENTIFIER=com.mawe.unittest
fi

INFO=$(cat <<END
<?xml version="1.0" encoding="UTF-8"?>
<!DOCTYPE plist PUBLIC "-//Apple//DTD PLIST 1.0//EN" "http://www.apple.com/DTDs/PropertyList-1.0.dtd">
<plist version="1.0">
<dict>
    <key>CFBundleDevelopmentRegion</key>
    <string>en</string>
    <key>CFBundleExecutable</key>
    <string>$EXECUTABLE_NAME</string>
    <key>CFBundleIdentifier</key>
    <string>$PRODUCT_BUNDLE_IDENTIFIER</string>
    <key>CFBundleInfoDictionaryVersion</key>
    <string>6.0</string>
    <key>CFBundleName</key>
    <string>$EXECUTABLE_NAME</string>
    <key>CFBundlePackageType</key>
    <string>APPL</string>
    <key>CFBundleShortVersionString</key>
    <string>1.0</string>
    <key>CFBundleVersion</key>
    <string>1</string>
    <key>LSRequiresIPhoneOS</key>
    <true/>
    <key>UILaunchStoryboardName</key>
    <string>LaunchScreen</string>
    <key>UIMainStoryboardFile</key>
    <string>Main</string>
    <key>UIRequiredDeviceCapabilities</key>
    <array>
        <string>armv7</string>
    </array>
    <key>UIStatusBarHidden</key>
    <true/>
    <key>UISupportedInterfaceOrientations</key>
    <array>
        <string>UIInterfaceOrientationPortrait</string>
        <string>UIInterfaceOrientationLandscapeLeft</string>
        <string>UIInterfaceOrientationLandscapeRight</string>
    </array>
</dict>
</plist>
END
)

echo $INFO > $TMP/Info.plist

# finds the first identity
#  removes the firsat 2 words of the line
#  strips leading whitespace
#  removces quotes around the string
IDENTITY=$(security find-identity -v -p codesigning | head -1 | awk '{ $1=""; $2=""; print}' | sed -e 's/^[[:space:]]*//' | sed -e 's/^"//' -e 's/"$//')

rm -rf "$TMP/_CodeSignature"


PROVISION="${TMP}/provision.plist"
ENTITLEMENTS="${TMP}/entitlement.plist"

security cms -D -i "${MOBILEPROVISION}" > "${PROVISION}"
/usr/libexec/PlistBuddy -x -c 'Print :Entitlements' "${PROVISION}" > "${ENTITLEMENTS}"

rm $PROVISION

echo codesign -s $IDENTITY $TMP
codesign -f -s "$IDENTITY" --entitlements "$ENTITLEMENTS" $TMP
