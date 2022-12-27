var a = document.getElementById("blah");
function readUrl(input){
if(input.files){
    var reader = new FileReader();
    reader.readAsDataURL(input.files[0]);
    reader.onload=(e)=>{
        a.src = e.target.result;
    }
}
}

var inputFile = document.getElementById("inputFile");
removeImg=()=>{
   a.src="https://t4.ftcdn.net/jpg/02/51/95/53/360_F_251955356_FAQH0U1y1TZw3ZcdPGybwUkH90a3VAhb.jpg"; 
   inputFile.value=""; 
}