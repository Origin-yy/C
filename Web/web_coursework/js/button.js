// const goHomeBtn = document.getElementById("goHome");
// if (goHomeBtn) {
//     goHomeBtn.onclick = function () {
//         // console.log("location.href: " + location.href);
//         location.href = "animals.html";
//     };
//
// }
//
// const goBeautifulPageBtn = document.getElementById("goBeautifulPage");
// // console.log("goBeautifulPageBtn" + goBeautifulPageBtn);
// if(goBeautifulPageBtn){
//     goBeautifulPageBtn.onclick = function () {
//         // console.log("location.href: " + location.href);
//         location.href = "beautiful.html";
//     };
//
// }


// goContactUs

function setBtns() {
    let btnNames = ["goContactUs", "goHome", "goBeautifulPage","doLogin"];
    let btnReacts = ["contactUs.html", "animals.html", "beautiful.html","login.html"];
    let btn;
    for (let i = 0; i < btnNames.length; i++) {
        btn = document.getElementById(btnNames[i]);
        // console.log("btnNames[i]: " + btnNames[i]);
        // console.log("btn: " + btn);
        // console.log("i: "+i);
        if(btn==null)continue;
        btn.onclick = function (ev) {
            location.href = btnReacts[i];
        };
    }
}

setBtns();