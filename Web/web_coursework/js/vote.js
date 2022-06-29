function putVoteOnclick() {

    let $vote = $("#vote");
    $vote.find(".vote-btn").click(function () {

        let li = $(this).parent();
        animalName = li.text().replaceAll("投票", "");
        val = li.val().trim();
        // console.log("val");
        // console.log(val);
        // console.log(li.value());
        // console.log(li.text());
        // console.log(li);
        // console.log("animalName");
        // console.log(animalName);
        // span = $(this).siblings("span");
        p = $(this).siblings("p");
        // console.log(p);
        scoreText=p.text().replaceAll("分数: ","");
        score = parseInt(scoreText);
        // console.log("score");
        // console.log(score);
        score++;
        scoreTextOut="分数: "+score ;
        p.text(scoreTextOut);

    });
}

function putVote() {

    let onRow = `  <div class="col">
                    <div class="img-container">
<!--                        style="display: block"-->
                        <img src="images/#imgName#.jpg" class="heart-jump " alt="heart" />
                    </div>
                    <div class=" "></div>
<!--                    box-->
<!-- style="background-color:yellow;"-->
                    <div class="">
                        <button class="vote-btn hover-shake">投票</button>
                        <p class="">分数: 1</p> 
<!--                        margin-left-10vw-->
                    </div>
                </div>`;

    let imgNameList = ["fish", "doge", "公鸡", "dogkawi", "catkawai"];
    let rowsHtml = "";
    for (let i = 0; i < imgNameList.length; i++) {
        rowsHtml += onRow.replaceAll("#imgName#", imgNameList[i]);
    }
    $("#vote").html(rowsHtml);
}

putVote();
putVoteOnclick();