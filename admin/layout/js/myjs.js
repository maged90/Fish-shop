// placeHolder Funtion Handle 
	focusplaceHolder = (x)=>{
		x.setAttribute('place', x.placeholder);
		x.placeholder = "";
	}
	blurplaceHolder = (x)=>{
		x.placeholder = x.getAttribute('place');
		x.removeAttribute('place');
	}

