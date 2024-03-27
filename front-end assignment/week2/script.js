function HighLight(){
//实现点击哪个笔记哪个笔记高亮
    const nodeStatus = document.getElementsByClassName('nodeStatus');
    // 遍历盒子，并为每个盒子添加点击事件监听器    伪数组
    for (let i = 0; i < nodeStatus.length; i++) {
        nodeStatus[i].addEventListener('click', function() {
            // 将当前点击的盒子设置为蓝色
            this.style.backgroundColor = '#ced9f2';
            // 将其他盒子恢复为原始状态
            for (let j = 0; j < nodeStatus.length; j++) {
                if (nodeStatus[j] !== this) {
                    nodeStatus[j].style.backgroundColor = '#ffff';
                }
            }
        });
    }
}


let notes = JSON.parse(localStorage.getItem('notes')) || [];
//获取本地存储 有则解析，无则为空数组
const noteInput = document.getElementById('note_textarea');
const noteList = document.getElementById('nodeList');


function saveNotes(){
  localStorage.setItem('notes',JSON.stringify(notes));
}

function displayNotes(){
  noteList.innerText=``
//初始值 保留一个欢迎的笔记    要给nodeTitle绑定 因为span盒子没有nodeTitle那么大 防止点到nodeTitle
notes.forEach((note,index) => {
  const div = document.createElement('div');
  div.classList.add('nodeStatus');
  div.innerHTML = `
              <div class="nodeTitle " data-index="${index}">
              <span class="${index}" data-index="${index}">${note}</span>
              <button class="icon_button iconfont icon-guanbi1 deleteBtn" data-index="${index}"></button>
            </div>
          </div>
  `;
  noteList.appendChild(div);
});           
}

//添加新的笔记
function addNote(){
  const noteText = "新笔记..";
    notes.unshift(noteText);
    //把笔记添加到数组开头 会改变原来的数组
    saveNotes();
    displayNotes();
}

//删除笔记
    function deleteNote(index) {
      notes.splice(index, 1);
      saveNotes();
      displayNotes();
    }

//修改笔记内容
function editNote(index) {
      removeTextareaEventListener();
      //获取克隆后的新textarea
      const note_textarea = document.getElementById('note_textarea');
      //同步笔记文本到输入框内
      note_textarea.value=notes[index]
      //重新绑定事件 实现实时修改笔记内容
      note_textarea.addEventListener('input',function(){
        notes[index] = note_textarea.value;
      saveNotes();
      displayNotes();
      })

    }
//增加笔记
const addNodeButton = document.getElementById('addNodeButton');
addNodeButton.addEventListener('click',function(){
  addNote();
  HighLight();
});
//删除笔记
noteList.addEventListener('click',function(event){
  if(event.target.classList.contains('deleteBtn')){
    const index = event.target.dataset.index;
    deleteNote(index);
  }
})
//修改笔记
noteList.addEventListener('click',function(event){
  const index = event.target.dataset.index;
  console.log(index);
editNote(index);
HighLight()
})


//移除监听事件
function removeTextareaEventListener(){
const textarea = document.getElementById('note_textarea');
// 创建一个新的<textarea>元素，以替换现有的<textarea>元素   将属性等全部克隆 实现移除监听事件 防止同时更改多个笔记
const newTextarea = document.createElement('textarea');
newTextarea.name = textarea.name;
newTextarea.id = textarea.id;
newTextarea.cols = textarea.cols;
newTextarea.rows = textarea.rows;
newTextarea.className = textarea.className;
newTextarea.placeholder = textarea.placeholder;
newTextarea.spellcheck = textarea.spellcheck;
newTextarea.value = textarea.value;
// 将新<textarea>元素替换现有的<textarea>元素
textarea.parentNode.replaceChild(newTextarea, textarea);
}

//搜索笔记
function searchNotes(keyword){
  const regex = new RegExp(keyword,'gi');
  noteList.querySelectorAll('.nodeTitle').forEach(item =>  {
    const noteText = item.querySelector('span').textContent;
    const highlightedText = noteText.replace(regex, match => `<span class="highlight">${match}</span>`);
    item.querySelector('span').innerHTML = highlightedText;
  })
}

const search_input=document.querySelector('.search_input');
search_input.addEventListener('input',function(event){
  const keyword = event.target.value.trim();
  searchNotes(keyword);
})

