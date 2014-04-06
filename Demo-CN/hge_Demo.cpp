/*
** Haaf's Game Engine 1.8
**
** ƽ���ͼ�̳�
*/


#include "hge.h"// ����hgeͷ�ļ�

#include "GfxFont.h"// ����hgefontͷ�ļ�
#include "hgesprite.h"
#include <stdio.h>

HGE *hge = 0;//����һ��ָ��hge���ָ�롣

GfxFont* fnt;//��������ָ��,

//��ʾͼƬ
hgeSprite *spr[3];// ����������ָ��

HTEXTURE tex[3];//����һ�� texture(����)����

const int rows=8,cols=8;//���� �б�ź��б��


bool FrameFunc()//�߼�����,�˺���ÿһ֡���ᱻ����һ�Σ��������Ϸѭ���Ĵ��������
{	
	
	
	//���"ESC"���Ƿ񱻰���,������� "true"  ��ֹͣ���г���.	
	if (hge->Input_GetKeyState(HGEK_ESCAPE)) return true;


	return false;//��������ʱ���Ƿ���false,����ϣ��������ֹʱ����true
}


bool RenderFunc()// ���ƺ������������Ⱦ����������
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
	//��ʼ��Ⱦͼ��
	hge->Gfx_BeginScene(); 

	hge->Gfx_Clear(0xFF000000);//��ĳ��ɫ������OxFF000000Ϊ͸����Ϊ0�ĺ�ɫ
	for(int i=0;i<rows*cols;i++){
		int rowNum=i/cols;//���б��
		int colNum=i%cols;//���б��
		int x=colNum*100;//����ͼX����	
		int y=rowNum*100;//����ͼY����
		spr[mapIndex[i]]->Render(x,y);//��ָ��λ��ƴ�ӵ�ͼ  
	}
	

	//����������ɫ
	fnt->SetColor(0xFF00FFFF);
	//��Ⱦ��ʽ�����ı��ַ���(��ĻX����,��ĻY����,���з����,�ı��ַ���)
	fnt->Print(200,200,"��ã���ͼ��Hello!");
	
	//������Ⱦͼ��
	hge->Gfx_EndScene();
	//����ϣ��������ֹʱ����true��	//����true���� System_Start����ִ��
	//���򷵻�false��	
	return false;

}


int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)//WinMain �������������ڡ�
{

	hge = hgeCreate(HGE_VERSION);//����HGE�ӿڣ���������ΪHGE_VERSION

	
	hge->System_SetState(HGE_FRAMEFUNC, FrameFunc);//�����߼�����ΪFrameFunc����
	
	hge->System_SetState(HGE_RENDERFUNC,RenderFunc);//���û��ƺ���ΪRenderFunc����
	
	hge->System_SetState(HGE_TITLE, "ƽ���ͼ");// ���ô��ڱ���

	hge->System_SetState(HGE_SCREENWIDTH, 800);//���򴰿ڿ��
	hge->System_SetState(HGE_SCREENHEIGHT, 800);//���򴰿ڸ߶�
	hge->System_SetState(HGE_WINDOWED, true);//�Ƿ��Ǵ���ģʽ��Ĭ���� 800x600
	hge->System_SetState(HGE_USESOUND, false);//ʹ��������Դ

	hge->System_SetState(HGE_SHOWSPLASH, false);//ȥ��HGE��ʼ��LOGO 
	hge->System_SetState(HGE_HIDEMOUSE,false); //�������



	if(hge->System_Initiate())//��ʼ�����������������Ӳ�����������򴰿ڡ�
	{
		char filename[20]="";
		fnt= new GfxFont("���񻪹������",30,false,FALSE,true);// ���飬���壬��б�壬��ƽ��																	//***


		for (int i=0;i<3;i++)
		{
			sprintf(filename,"%d.png",i);//	//������I ��ӡ��һ�� I.png �ַ���������filename�С�
		
			tex[i]=hge->Texture_Load(filename);//����·������ͼƬ·���ͺ�׺�����������Ŀ¼
			if(!tex[i])//����Ƿ�ͼƬ�ɹ�����
			{	
				// ����³�ʼ��ʧ����ʾ������Ϣ
				MessageBox(NULL, hge->System_GetErrorMessage(), "Error tex[i]tex", MB_OK | MB_ICONERROR | MB_APPLMODAL);
		}
		
		//				(tex,ͼƬ����ʾ��ʼλ��X,��ʼλ��Y,ͼƬ��,ͼƬ��)
		spr[i]=new hgeSprite(tex[i],0,0,100,100);//��ʼ������spr������ָ��texΪ��������  
		if(!spr)//����Ƿ�ɹ�����
		{	
			// ����³�ʼ��ʧ����ʾ������Ϣ
			MessageBox(NULL, hge->System_GetErrorMessage(), "Error spr", MB_OK | MB_ICONERROR | MB_APPLMODAL);
		}
	}



		hge->System_Start();//����FrameFunc().����. ����ɹ��򷵻�true�����򷵻�false 
	}
	else
	{	
		// ����³�ʼ��ʧ����ʾ������Ϣ
		MessageBox(NULL, hge->System_GetErrorMessage(), "Error", MB_OK | MB_ICONERROR | MB_APPLMODAL);
	}
	for (int i=0;i<3;i++)
	{
		
	hge->Texture_Free(tex[i]);//�ͷ�����

	delete spr[i];//�ͷž���
	}
	delete fnt;//�ͷ�����
	hge->System_Shutdown(); //��ԭ��Ƶģʽ���ͷ������ѷ������Դ�������ٳ��򴰿ڡ�
	//ɾ����Դ

	hge->Release();//�ͷ�HGE�ӿڲ��ڱ�Ҫʱɾ��HGE����

	return 0;
}
