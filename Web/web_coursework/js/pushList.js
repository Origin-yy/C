
lis = [];
linkPreffix="images/";
let li;
for (let i = 0; i < animals.length; i++) {
    li = oneLi.replaceAll("animalName", animals[i]);
    li = li.replaceAll("imgName", animalImgs[i]);
    li = li.replaceAll("link", linkPreffix + animalImgs[i]);

    lis.push(li);

}
$("#listAnimals ul").html(lis);