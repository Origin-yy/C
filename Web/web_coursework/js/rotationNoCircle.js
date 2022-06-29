/**
 * Created by Administrator on 16-6-23.
 */
var iCount = 2;
// 不能两个地方都写 onload
if (document.getElementById("a1") != null) {
    document.getElementById("a1").onclick = function () {
        iCount = 1;
        changebgcolor(iCount);
    }
}
if (document.getElementById("a2") != null) {
    document.getElementById("a2").onclick = function () {
        iCount = 2;
        changebgcolor(iCount);
    }
}
if (document.getElementById("a3") != null) {
    document.getElementById("a3").onclick = function () {
        iCount = 3;
        changebgcolor(iCount);
    }
}
if (document.getElementById("a4") != null) {
    document.getElementById("a4").onclick = function () {
        iCount = 4;
        changebgcolor(iCount);
    }
}
var iCarouselid = window.setInterval("carousel()", 2000);
// 两秒钟换一次图片

function carousel() {
    var sImgSrc = eval("'images/b-ad'+iCount.toString()+'.jpg'");
    var sAchange = eval("'a'+iCount.toString()");
    /*记录需要变回颜色的链接顺序。*/
    var iA = iCount - 1;
    if (iA == 0) {
        iA = 4;
    }
    // 她前面一个要变回原样了
    var sArestore = eval("'a'+iA.toString()");
    document.getElementById("banner").src = sImgSrc;
    document.getElementById(sAchange).style.backgroundColor = "deepskyblue";
    document.getElementById(sArestore).style.backgroundColor = "dodgerblue";
    iCount = iCount + 1;
    if (iCount == 5) {
        iCount = 1;
    }
}

function changebgcolor(iNum) {
    document.getElementById("banner").src = eval("'images/b-ad'+iNum.toString()+'.jpg'");
    for (var iC = 1; iC <= 4; iC++) {
        var sA = eval("'a'+iC.toString()");
        // 获得a名字
        if (iC == iNum) {
            document.getElementById(sA).style.backgroundColor = "deepskyblue";
        } else {
            document.getElementById(sA).style.backgroundColor = "dodgerblue";
        }
    }
}

