function setBtns() {
    let btnNames = ["goContactUs", "goHome", "goBeautifulPage","doLogin"];
    let btnReacts = ["contactUs.html", "animals.html", "beautiful.html","login.html"];
    let btn;
    for (let i = 0; i < btnNames.length; i++) {
        btn = document.getElementById(btnNames[i]);

        if(btn==null)continue;
        btn.onclick = function (ev) {
            location.href = btnReacts[i];
        };
    }
}

setBtns();