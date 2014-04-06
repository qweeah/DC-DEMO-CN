/*
** Haaf's Game Engine 1.8
**
** 平面地图教程
*/


#include "hge.h"// 包含hge头文件

#include "GfxFont.h"// 包含hgefont头文件
#include "hgesprite.h"
#include <stdio.h>

HGE *hge = 0;//创建一个指向hge类的指针。

GfxFont* fnt;//定义字体指针,

//显示图片
hgeSprite *spr[3];// 创建精灵类指针

HTEXTURE tex[3];//定义一个 texture(纹理)对象

const int rows=8,cols=8;//定义 行编号和列编号


bool FrameFunc()//逻辑函数,此函数每一帧都会被调用一次，把你的游戏循环的代码在这里。
{	
	
	
	//检测"ESC"键是否被按下,如果返回 "true"  则停止运行程序.	
	if (hge->Input_GetKeyState(HGEK_ESCAPE)) return true;


	return false;//程序正常时总是返回false,当你希望程序终止时返回true
}


bool RenderFunc()// 绘制函数，将你的渲染代码放在这里。
{
	int mapIndex[rows*cols]={
			2,2,2,2,2,2,2,2,
			2,0,0,0,0,0,0,2,
			2,0,1,1,1,1,0,2,
			2,0,1,0,0,1,0,2,
			2,0,1,0,0,1,0,2,
			2,0,1,1,1,1,0,2,
			2,0,0,0,0,0,0,2,
			2,2,2,2,2,2,2,2	};
	//开始渲染图像
	hge->Gfx_BeginScene(); 

	hge->Gfx_Clear(0xFF000000);//以某颜色清屏，OxFF000000为透明度为0的黑色
	for(int i=0;i<rows*cols;i++){
		int rowNum=i/cols;//求行编号
		int colNum=i%cols;//求列编号
		int x=colNum*100;//求贴图X坐标	
		int y=rowNum*100;//求贴图Y坐标
		spr[mapIndex[i]]->Render(x,y);//在指定位置拼接地图  
	}
	

	//设置字体颜色
	fnt->SetColor(0xFF00FFFF);
	//渲染格式化的文本字符串(屏幕X坐标,屏幕Y坐标,排列分类符,文本字符串)
	fnt->Print(200,200,"你好，地图！Hello!");
	
	//结束渲染图像
	hge->Gfx_EndScene();
	//当你希望程序终止时返回true，	//返回true将从 System_Start往下执行
	//否则返回false。	
	return false;

}


int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)//WinMain 函数，程序的入口。
{

	hge = hgeCreate(HGE_VERSION);//创建HGE接口，参数必须为HGE_VERSION

	
	hge->System_SetState(HGE_FRAMEFUNC, FrameFunc);//设置逻辑函数为FrameFunc函数
	
	hge->System_SetState(HGE_RENDERFUNC,RenderFunc);//设置绘制函数为RenderFunc函数
	
	hge->System_SetState(HGE_TITLE, "平面地图");// 设置窗口标题

	hge->System_SetState(HGE_SCREENWIDTH, 800);//程序窗口宽度
	hge->System_SetState(HGE_SCREENHEIGHT, 800);//程序窗口高度
	hge->System_SetState(HGE_WINDOWED, true);//是否是窗口模式，默认是 800x600
	hge->System_SetState(HGE_USESOUND, false);//使用声音资源

	hge->System_SetState(HGE_SHOWSPLASH, false);//去掉HGE开始的LOGO 
	hge->System_SetState(HGE_HIDEMOUSE,false); //设置鼠标



	if(hge->System_Initiate())//初始化引擎所需的所有软硬件并创建程序窗口。
	{
		char filename[20]="";
		fnt= new GfxFont("青鸟华光简综艺",30,false,FALSE,true);// 宋书，粗体，非斜体，非平滑																	//***


		for (int i=0;i<3;i++)
		{
			sprintf(filename,"%d.png",i);//	//把整数I 打印成一个 I.png 字符串保存在filename中。
		
			tex[i]=hge->Texture_Load(filename);//根据路径载入图片路径和后缀，这里是相对目录
			if(!tex[i])//检测是否图片成功载入
			{	
				// 如果下初始化失败显示错误消息
				MessageBox(NULL, hge->System_GetErrorMessage(), "Error tex[i]tex", MB_OK | MB_ICONERROR | MB_APPLMODAL);
		}
		
		//				(tex,图片的显示起始位置X,起始位置Y,图片宽,图片高)
		spr[i]=new hgeSprite(tex[i],0,0,100,100);//初始化精灵spr，并且指定tex为它的纹理  
		if(!spr)//检测是否成功载入
		{	
			// 如果下初始化失败显示错误消息
			MessageBox(NULL, hge->System_GetErrorMessage(), "Error spr", MB_OK | MB_ICONERROR | MB_APPLMODAL);
		}
	}



		hge->System_Start();//运行FrameFunc().函数. 如果成功则返回true。否则返回false 
	}
	else
	{	
		// 如果下初始化失败显示错误消息
		MessageBox(NULL, hge->System_GetErrorMessage(), "Error", MB_OK | MB_ICONERROR | MB_APPLMODAL);
	}
	for (int i=0;i<3;i++)
	{
		
	hge->Texture_Free(tex[i]);//释放纹理

	delete spr[i];//释放精灵
	}
	delete fnt;//释放字体
	hge->System_Shutdown(); //复原视频模式，释放所有已分配的资源，并销毁程序窗口。
	//删除资源

	hge->Release();//释放HGE接口并在必要时删除HGE对象。

	return 0;
}
