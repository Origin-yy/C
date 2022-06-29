oneLi = `
    <li><a class="selling" href="link" target="_blank">animalName</a>
                <div class="curr">
                    <div class="p-img">
                        <a title="animalName" href="link">
                            <img src="images/imgName" alt="animalName">
                        </a>
                    </div>
                    <div class="p-name">
                        <a title="animalName" href="link">animalName</a>

                    </div>
                </div>
            </li>
`;
// 水母不行 熊猫 老虎
animals = ["鲨鱼", "狗", "猫","鸭子","🦊","长颈鹿","狮子🦁","熊(●￣(ｴ)￣●)","^(*￣(oo)￣)^","豹子","乌龟🐢","北极熊","狼🐺"];
animalImgs = ["sharkBIgNose.jpg", "dog.jpg", "cat.jpg", "duck.jpg", "fox.jpg", "giraffe.jpg", "lion2.jpg",
     "bear.jpg", "pig.jpg", "豹子.jpg", "乌龟.jpg", "北极熊.jpg", "狼.jpg"];
// animalLinks = ["sharkBIgNose.jpg", "dog.jpg", "cat.jpg", "duck.jpg", "fox.jpg", "jellyfishFlash.jpg", "lion2.jpg"];
lis = [];
linkPreffix="images/";
let li;
for (let i = 0; i < animals.length; i++) {
    li = oneLi.replaceAll("animalName", animals[i]);
    li = li.replaceAll("imgName", animalImgs[i]);
    li = li.replaceAll("link", linkPreffix + animalImgs[i]);

    lis.push(li);
    // lis.push(oneLi.replaceAll("$animalName",animals[i]));
}
// console.log("lis[0]:"+lis[0]);
// console.log("$animalName111".replaceAll("$animalName", "hello"));
// console.log("animalName111".replaceAll("animalName", "hello"));
// replace的时候不能有$
$("#listAnimals ul").html(lis);