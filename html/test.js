var a = document.getElementById("blah");
function readUrl(input){
if(input.files){
    var reader = new FileReader();
    reader.readAsDataURL(input.files[0]);
    reader.onload=(e)=>{
        a.src = e.target.r-esult;
    }
}
}

var inputFile = document.getElementById("inputFile");
removeImg=()=>{
   a.src="http://placehold.it/180"; 
   inputFile.value=""; 
}
