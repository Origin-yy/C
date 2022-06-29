function nowTime() {
    // 上午下午
    function current() {
        var oDate = new Date();
        var year = oDate.getFullYear();
        var month = oDate.getMonth() + 1;
        var date = oDate.getDate();
        var day = oDate.getDay();
        // console.log(day);
        var week = ["日", "一", "二", "三", "四", "五", "六",];
        var hours = oDate.getHours();
        var minutes = oDate.getMinutes();
        var seconds = oDate.getSeconds();
        var str = "";
        str = year + "年" + change(month) + "月" + change(date) + "日  星期" + week[day] +
            change(hours) + ":" + change(minutes) + ":" + change(seconds);
        if (hours === 12) {
            if (minutes > 12) {
                str += "下午";
            } else if (minutes === 0) {
                if (seconds > 0) {
                    str += "下午";
                } else {
                    str += "上午";
                }
            } else {
                str += "上午";
            }
        } else if (hours > 12) {
            str += "下午";
        } else {
            str += "上午";
        }
        document.getElementById("currentTime").innerHTML = str;
    }

    setInterval(current, 500);


}

function change(data) {
    return data <= 9 ? "0" + data : data;
}

nowTime();