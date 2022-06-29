String.prototype.replaceAll = function (oldStr, newStr) {
    return this.replace(new RegExp(oldStr, "gm"), newStr);
};
// https://www.cnblogs.com/mq0036/p/6013225.html


function frontDelStr(oldStr, dontWant) {

    if (dontWant === "") {
        return oldStr;
    }
    let oldStrLen = (oldStr).length;
    let dontWantLen = (dontWant).length;
    let minLen = Math.min(oldStrLen, dontWantLen);

    let iOld = 0;
    let iDont = 0;

    let iRes = 0;
    let iNow = 0;
    while (true) {


        if (!(oldStr[iOld] === dontWant[iDont])) {
            return oldStr.substring(iRes, oldStrLen);
        }

        iNow++;
        if (iNow - iRes === dontWantLen) {
            iRes += dontWantLen;

        }
        if (iDont === minLen - 1 || iOld === minLen - 1)
            return oldStr.substring(iRes, oldStrLen);

        iOld++;
        iDont++;

    }
}

function backDelStr(oldStr, dontWant) {
    //todo ,completed
    if (dontWant === "") {
        return oldStr;
    }
    let oldStrLen = (oldStr).length;
    let dontWantLen = (dontWant).length;
    let iOld = oldStrLen - 1;
    let iDont = dontWantLen - 1;

    let iRes = oldStrLen;
    let iNow = oldStrLen;
    while (true) {


        if (!(oldStr[iOld] === dontWant[iDont])) {
            return oldStr.substring(0, iRes);
        }

        iNow -= 1;
        if (iRes - iNow === dontWantLen) {
            iRes -= dontWantLen;

        }
        // https://www.w3school.com.cn/js/jsref_substring.asp
        if (iDont === 0 || iOld === 0)
            return oldStr.substring(0, iRes);

        iOld--;
        iDont--;

    }

}