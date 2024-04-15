
//获得根节点
const root = document.documentElement;
//登录注册模块
document.querySelector('#loginform').addEventListener('submit',function(event){
  event.preventDefault(); //防止默认事件（表单直接提交）
  //禁用按钮 防止多次提交
  submitBtn.disabled = true;
  //获得数据
  const username = document.querySelector('#username').value;
  const password = document.querySelector('#password').value;
  const usertype = document.querySelector('input[name="usertype"]:checked').value
  //调用接口
  let fetchUrl;
  if(sign){
    fetchUrl = "http://localhost:3000/api/auth/login";
  }
  else{
    fetchUrl = "http://localhost:3000/api/auth/register";
  }
  fetch(fetchUrl,{
    method:"POST",
    headers:{
      "Content-Type":"aplication/json",
    },
    body:JSON.stringify({
      username:username,
      password:password,
      usertype
    })
  })
  .then((response) =>{
//改变弹窗的颜色
root.style.setProperty('--alert-color', '#00a76f'); // 修改为红色
    if(response.status >= 400 ){
root.style.setProperty('--alert-color', '#FADAD8'); // 修改为红色
    }
      return response.json();
  })
  .then(data =>{
      //登录成功
      alert(`${data.message}`);
  })
  .catch(()=>{
root.style.setProperty('--alert-color', '#FADAD8'); // 修改为红色
      //网络故障
      alert("网络故障");
  })
  setTimeout(() => {
    submitBtn.disabled =false;
  }, 2000);
})

//登录按钮active
const submitBtn = document.querySelector('#submitBtn');
submitBtn.addEventListener('mouseover',function(){
  submitBtn.classList.add('bgcolor');
})
submitBtn.addEventListener('mouseleave',function(){
  submitBtn.classList.remove('bgcolor');
})


//账号密码 交互
  const username = document.querySelector('#username');
  const password = document.querySelector('#password');
  const usernameSpan = document.querySelector('#usernameSpan');
  const passwordSpan = document.querySelector('#passwordSpan');
  const usernameError =document.querySelector('#usernameError');
  const passwordError =document.querySelector('#passwordError');
input(username,usernameSpan,usernameError);
input(password,passwordSpan,passwordError);
  function input(element,span,error){
element.addEventListener('input',function(){
  if(element.value.trim()===''){
    span.classList.add('red');
    error.style.display='block';
  }else{
        span.classList.remove('red');
  span.classList.add('green');
      error.style.display='none';
  }
})
}


//注册页面
let sign = 1;
  let registerbtn = document.querySelector('.registerbtn');
registerbtn.addEventListener('click',function(){

const registerbtnSpan = document.querySelector('.registerbtn span')
const h2 = document.querySelector('.leftSide h2');
const title = document.querySelector('.title');
const alert_content = document.querySelector('.alert_content');
const fr = document.querySelector('.fr');
const submitSpan = document.querySelector('#submitSpan');
const secondarySpan = document.querySelector('#secondarySpan')
const userState = document.querySelector('#userState')
  if(sign){
    registerbtnSpan.innerText='立即登录';
    userState.innerText='老用户?'
    secondarySpan.innerText='立即登录'
      h2.innerText="Hi,欢迎新用户！"
      title.innerText="注册 Adam System"
      alert_content.innerText="注册信息： 用户名：adam 密码：123456"
      fr.style.display="none"
      submitSpan.innerText="注 册"
      sign=0;
  }else{
    registerbtnSpan.innerText='立即注册';
    userState.innerText='新用户?'
    secondarySpan.innerText='立即注册'
      h2.innerText="Hi,欢迎回来！"
      title.innerText="登录 Adam System"
      alert_content.innerText="登录信息： 用户名：adam 密码：123456"
      fr.style.display="block"
      submitSpan.innerText="登 录"
      sign=1;    
  }
})

















