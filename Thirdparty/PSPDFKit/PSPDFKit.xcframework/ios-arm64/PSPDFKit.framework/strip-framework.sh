#  strip-framework.sh
#  Copyright © 2010-2020 PSPDFKit GmbH. All rights reserved.
#
#  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
#  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
#  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
#  This notice may not be removed from this file.

function message {
    echo "[PSPDFKit] strip-framework.sh: $1"
}

cd "$BUILT_PRODUCTS_DIR/$FRAMEWORKS_FOLDER_PATH" || exit 1

frameworks=("PSPDFKit" "PSPDFKitUI" "Instant" "PSPDFKitOCR")

message "Xcode 12 automatically handles the \`.bcsymbolmap\` and \`.dSYM\` files."
message "This script is no longer required and will be removed in a future update."
message "You can safely remove the Run Script Phase below the Embed Frameworks build phase."
message "If you're archiving for Mac Catalyst and you removed Run Script Phase, you need manually delete this script by running \`rm PSPDFKit.xcframework/*/PSPDFKit.framework/strip-framework.sh\`."

# Remove the scripts from the framework for archives to avoid "ITMS-90238: Invalid Signature"
if [[ $(pwd) == *"/Build/Intermediates.noindex/ArchiveIntermediates/"* ]]; then
	for framework in $frameworks; do
	    strip_framework_script_path="$BUILT_PRODUCTS_DIR/$FRAMEWORKS_FOLDER_PATH/$framework.framework/strip-framework.sh"
	    if [ -f "$strip_framework_script_path" ]; then
	        rm "$strip_framework_script_path"
	        message "Removed $strip_framework_script_path from $framework"
	    fi
	done
fi
