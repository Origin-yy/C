commentLi = `
 <li>
            <fieldset class="people-comment">
                <legend>##floorCnt#楼</legend>
                用户 #username# 如是说
                <p>#commentTime#</p>
                <p>#content#</p>
                <button id="raiseCmt#cnt#" class="box box-5vw comment-btn raise-comment hover-shake">评论</button>
                 <fieldset class="box-margin">
                    <legend>#from#  to  #username# </legend>
                     #fromToContent#
                    <div>
                        <button id="delBtn#cnt#" class="box box-5vw comment-btn del-btn hover-shake">删除</button>
                        </div>
                </fieldset>
                <fieldset class="people-comment comment-to-comment-field">
                    <legend>致亲爱的 #username# </legend>
                    <label>好兄弟(姐妹) 你有什么话要说
                        <textarea id="cmtTxt#cnt#" class="textarea edge-glow contact-input comment-to-comment"></textarea>
                    </label>
                    <div>
                    <button id="submit#cnt#" class="box box-5vw comment-btn submit-btn hover-shake">提交</button>
                      <input id="from#cnt#" type="hidden" value="#from#" name="from">
                        <input id="to#cnt#" type="hidden" value="#to#" name="to">
                    </div>
                </fieldset>
            </fieldset>

        </li>`;


cmt2CmtField = `   <fieldset class="box-margin">
                    <legend>#from#  to  #to# </legend>
                    #content#
                    <div>
                        <button class="box box-5vw comment-btn del-btn">删除</button></div>
                </fieldset>`;

commentObjList = [{
    username: "java", content: "真不错", fromTo: {
        from: "joseph", to: "java", content: "可爱"
    }, commentTime: "2021-10-3 13:30:34"
}, {
    username: "miku", content: "漂亮", fromTo: {
        from: "jonathon", to: "miku", content: "美啊"
    }, commentTime: "2021-10-3 13:30:34"
}];

function putComments() {

    let htmlLis = "";
    let commentLiHtml;
    for (let i = 0; i < commentObjList.length; i++) {
        let commentObj = commentObjList[i];
        // commentLiHtml = commentLi.replaceAll("username", commentObj.username);
        // commentLiHtml = commentLiHtml.replaceAll("content", commentObj.content);
        // commentLiHtml = commentLiHtml.replaceAll("floorCnt", i + 1);
        commentLiHtml = replaceCommentLiHtml(commentLi, commentObj, i);
        // htmlLis+=commentLi.replaceAll("username",commentObj.username);
        // htmlLis+=commentLi.replaceAll("username",commentObj.username);
        htmlLis += commentLiHtml;
    }
    $("#commentList").html(htmlLis);

}

// https://www.runoob.com/jquery/traversing-parent.html
function replaceCommentLiHtml(commentLiHtml, commentObj, index) {
    // https://blog.csdn.net/weixin_33963594/article/details/86206313
    // 不是这个key里面的 floorCnt
    commentLiHtml = commentLiHtml.replaceAll("#username#", commentObj.username);
    commentLiHtml = commentLiHtml.replaceAll("#content#", commentObj.content);
    commentLiHtml = commentLiHtml.replaceAll("#floorCnt#", index + 1);
    commentLiHtml = commentLiHtml.replaceAll("#commentTime#", commentObj.commentTime);
    commentLiHtml = commentLiHtml.replaceAll("#cnt#", index);

    let oFromTo = commentObj.fromTo;
    commentLiHtml = commentLiHtml.replaceAll("#from#", oFromTo.from);
    commentLiHtml = commentLiHtml.replaceAll("#to#", oFromTo.to);
    commentLiHtml = commentLiHtml.replaceAll("#fromToContent#", oFromTo.content);

    // replaceKeyWords = ["username", "username", "floorCnt", "floorCnt", "floorCnt", "floorCnt", "floorCnt", "floorCnt"];
    // keys = commentObj.keys();
    // for (i = 0; i < replaceKeyWords.length; i++) {
    //     commentLiHtml = commentLiHtml.replaceAll(replaceKeyWords[i], keys[i]);
    // }
    return commentLiHtml;
}


 function putOnClick() {
    let $commentList = $("#commentList>li>fieldset");
    // $commentList.children(".comment-to-comment-field>div")
    let i = 0;
    let cmtField;
    let cmt2CmtField;
    let strId;

    // console.log($commentList[0]);

    function bindRaiseSubmitDelBtn(node, i) {
        // let strId = "#raiseCmt" + i;
        // console.log(strId);
        //
        // console.log(node.find(strId));
        // node.find(strId).on("onclick", function ()
        // raise-comment
        // node.find("#raiseCmt" + i)
        node.find(".raise-comment").bind("click", {index: i}, function () {
// document.getElementsByClassName()

//                 console.log("raise colic");

            // cmt2CmtField = $(this).find(".comment-to-comment-field");
            let cmt2CmtField = node.find(".comment-to-comment-field");
            cmt2CmtField.css("display", "block");
            // cmt2CmtField.css("background-color", "yellow");

        });
        // console.log(node);
        // node.children("#submit" + i).on("onclick", function () {
        // $(asEach[i]).bind("click",{index:i},clickHandler
        // node.children("#submit" + i).click(function () {
        // console.log(node.find("#submit" + i));
        // let submitBtn;

        // node.find("#submit" + i)
        // node.find(".submit-btn").bind("click", {index: i},
        // node.find(".submit-btn").on("click", function (
        let submitBtn = node.find(".submit-btn");
        submitBtn.unbind();
        submitBtn.bind("click", function () {

                // cmtField = node.parent();
                cmtField = node;
// node =   <fieldset class="people-comment comment-to-comment-field">
                // console.log('on("onclick",');
                let cmt2CmtField = node.find(".comment-to-comment-field");
                // console.log("cmt2CmtField");
                // console.log(cmt2CmtField);
                let textarea = cmt2CmtField.find(".textarea");
                let cmtVal = textarea.val();
                let inputs = cmt2CmtField.find("input");
                let submitBtn = cmt2CmtField.find(".comment-btn");
                // console.log("inputs");
                // console.log(inputs);
                // console.log("submitBtn");
                // console.log(submitBtn);
                // cmt2CmtField.getElementsByTagName("textarea");
                // console.log("cmtVal");
                // console.log(cmtVal);
                // console.log("$(inputs[1]).val()");
                // console.log($(inputs[1]).val());
                // 点了一次 这个地方进来了  但是第二次才会发送
                let cmt2CmtObj = {
                    from: $(inputs[0]).val(),
                    to: $(inputs[1]).val(),
                    content: cmtVal,
                };
                addComment(cmtField, cmt2CmtObj);
                // function bindSubmitBtn(i) {
                //     // submitBtn.bind("click", {index: i}, function () {
                //     // submitBtn.on("click", {index: i}, function ()
                //     submitBtn.on("click",function () {
                //         console.log("submitBtn bind");
                //         addComment(cmtField, cmt2CmtObj);
                //     });
                // }

                // bindSubmitBtn(i);


                // let cmt2CmtObj = {
                //     from: inputs[0].value,
                //     to: inputs[1].value,
                //     content: cmtVal,
                // };

                // submitBtn.click(function () {

                // submitBtn.onclick = function () {
                //     // cmtField
                //     addCommentWithoutJq(cmtField, cmt2CmtObj);
                // }
            }
        );
        // node is cmtField
        // node.find("#delBtn" + i)
        let delBtn = node.find(".del-btn");
        delBtn.unbind();
        delBtn.bind("click", {index: i}, function () {
            $(this).parent().parent().css("display", "none");
        });
    }

    $commentList.each(function () {

            // console.log("this");
            // console.log($(this));
            //
            // console.log("comment-to-comment-field");
            // console.log(cmt2CmtField);

            // console.log(strId);
            // console.log("comment-to-comment-field submit");
            // console.log(  $(this).children(strId));
            // console.log("f[i");
            // console.log(i);
            // console.log($(this));


            bindRaiseSubmitDelBtn($(this), i);

            i++;
        }
    );
    // return new Promise((resolve, reject) => resolve(1));

}

function bindDel(cmtField) {
    cmtField.find(".del-btn").on("click", function () {
        $(this).parent().parent().css("display", "none");
    });
}

function bindCmtOnclickJq() {

// >.comment-btn
    let $cmt2CmtDiv = $(".comment-to-comment-field>div");
// console.log($cmt2CmtDiv);
// console.log($cmt2CmtDiv.children());
    let $cmt2CmtSubmitBtn = $cmt2CmtDiv.children(".comment-btn");
// console.log("$cmt2CmtSubmitBtn: ");
// console.log($cmt2CmtSubmitBtn);
    $cmt2CmtSubmitBtn.on("click", function () {
        // 提交评论的评论
        // $cmt2CmtDiv.children("input").val();
        // console.log("$cmt2CmtSubmitBtn click");
        let inputs = $cmt2CmtDiv.children("input");
        // console.log($cmt2CmtDiv.siblings());
        // console.log("label>.comment-to-comment");
        console.log(inputs);
        console.log(inputs[1]);
        // console.log($cmt2CmtDiv.siblings("label>.comment-to-comment"));
        let cmtVal = $cmt2CmtDiv.siblings("label").children(".comment-to-comment").val();
        let cmt2CmtObj = {
            from: inputs[0].value,
            to: inputs[1].value,
            content: cmtVal,
        };
        addComment($cmt2CmtDiv.parent().parent(), cmt2CmtObj);

    });
}

function addComment(node, cmt2CmtObj) {
    // cmt2CmtObj: {
    //     from: "miku", to:"joseph", content: "haha"
    // },
    // let html = node.html();
    // node.html(html + replaceCmt2CmtField(cmt2CmtObj));
    // putOnClick();
    node.append($(replaceCmt2CmtField(cmt2CmtObj)));
}

function addCommentWithoutJq(node, cmt2CmtObj) {
    let html = node.innerHTML;
    node.innerHTML = html + replaceCmt2CmtField(cmt2CmtObj);
}

function replaceCmt2CmtField(cmt2CmtObj) {
    let tmp = cmt2CmtField;
    // #from#  to  #to# </legend>
    // #content#
    console.log(cmt2CmtObj);
    tmp = tmp.replaceAll("#from#", cmt2CmtObj.from);
    tmp = tmp.replaceAll("#to#", cmt2CmtObj.to);
    return tmp.replaceAll("#content#", cmt2CmtObj.content);
}

// https://www.cnblogs.com/linkenpark/p/7838763.html

putComments();
// let $delBtn = $(".del-btn");
// $delBtn.click(function () {
//     $delBtn.parent().parent().css("display", "none");
// });

// let $commentBtn = $(".raise-comment");
// $commentBtn.click(function () {
//     // https://www.cnblogs.com/liuzhongqing/p/7381109.html
//     console.log($commentBtn.siblings("fieldset.comment-to-comment-field"));
//     $commentBtn.siblings("fieldset.comment-to-comment-field").css("display", "block");
// });
// async function run() {
//     await putOnClick();
//     run();
// }
putOnClick();
setInterval(putOnClick,1000);
// $(document).on("click",'.class',function(){});