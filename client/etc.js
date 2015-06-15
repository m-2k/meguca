/*
 Client-side helper functions
 */

let main = require('./main'),
	{_, state} = main;

// For mobile
function touchable_spoiler_tag(del) {
	del.html = '<del onclick="void(0)">';
}
exports.touchable_spoiler_tag = touchable_spoiler_tag;
main.oneeSama.hook('spoilerTag', touchable_spoiler_tag);

function imageUploadURL() {
	return (main.config.UPLOAD_URL || '../upload/') + '?id='
		+ state.page.get('connID');
}
exports.uploadURL = imageUploadURL;

// Keep the UI from locking as the loop iterates
function deferLoop(items, stack, func) {
	if (stack > items.length)
		stack = items.length;
	// Copy array to remove refference
	items = items.slice();
	for (let i = 0; i < stack; i++)
		func(items.pop());
	if (items.length)
		_.defer(deferLoop, items, stack, func);
}
exports.deferLoop = deferLoop;
