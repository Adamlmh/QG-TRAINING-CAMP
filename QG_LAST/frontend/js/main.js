function alert(content){
  const alert = document.createElement('div');
  alert.className='alert';
  alert.textContent=content;
  document.body.appendChild(alert);
  setTimeout(() => {
    document.body.removeChild(alert);
  }, 2000);
}
