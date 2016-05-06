function RTW_Sid2UrlHash() {
	this.urlHashMap = new Array();
	/* <Root>/Abs */
	this.urlHashMap["Fibonacci:15"] = "Fibonacci.c:73&Fibonacci.h:44";
	/* <Root>/Add */
	this.urlHashMap["Fibonacci:3"] = "Fibonacci.c:81&Fibonacci.h:45";
	/* <Root>/Divide */
	this.urlHashMap["Fibonacci:8"] = "Fibonacci.c:62";
	/* <Root>/Fn */
	this.urlHashMap["Fibonacci:1"] = "Fibonacci.c:40,84,117&Fibonacci.h:50,64&Fibonacci_data.c:22";
	/* <Root>/Fn_1 */
	this.urlHashMap["Fibonacci:2"] = "Fibonacci.c:44,87,120&Fibonacci.h:41,51,67&Fibonacci_data.c:25";
	/* <Root>/Gain */
	this.urlHashMap["Fibonacci:13"] = "Fibonacci.c:77&Fibonacci.h:79&Fibonacci_data.c:37";
	/* <Root>/Golden_ratio */
	this.urlHashMap["Fibonacci:10"] = "Fibonacci.c:68&Fibonacci.h:76&Fibonacci_data.c:34";
	/* <Root>/Saturation */
	this.urlHashMap["Fibonacci:7"] = "Fibonacci.c:47,59&Fibonacci.h:42,70,73&Fibonacci_data.c:28,31";
	/* <Root>/Subtract */
	this.urlHashMap["Fibonacci:11"] = "Fibonacci.c:67&Fibonacci.h:43";
	/* <Root>/Out1 */
	this.urlHashMap["Fibonacci:4"] = "Fibonacci.c:39&Fibonacci.h:56";
	/* <Root>/approximate_golden_ratio */
	this.urlHashMap["Fibonacci:9"] = "Fibonacci.c:61&Fibonacci.h:57";
	/* <Root>/error[%] */
	this.urlHashMap["Fibonacci:12"] = "Fibonacci.c:76&Fibonacci.h:58";
	this.getUrlHash = function(sid) { return this.urlHashMap[sid];}
}
	RTW_Sid2UrlHash.instance = new RTW_Sid2UrlHash();
