//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
#include <string>


#include "Unit1.h"
#include "Unit2.h"
#include "SubChange.h"
#include "FileOpen.h"
#include "Language.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;
bool Faster;
AnsiString File_Name="";
char type='o';
char lang='p';

//---------------------------------------------------------------------------


__fastcall TForm1::TForm1(TComponent* Owner)
        : TForm(Owner)
        {
        }




//---------------------------------------------------------------------------

//---------------------------------------------------------------------------

void __fastcall TForm1::Otwrz1Click(TObject *Sender)
{

   if (OpenDialog1->Execute())
   {
     try
     {
        File_Name = OpenDialog1->FileName;
        OpenFile(File_Name);
        int i=0;
        string w[10];
        while(i<10)
        {
                w[i]=Content->Lines->Strings[i].c_str();
                i++;
        }
        type=CheckType(w);
        DealWithType(type);
//-----------------------------------------------------------------

}

//----------------------------------------------------------------------------

     catch (...)
     {

        ShowMessage("B��d otwarcia pliku. Upewnij si�, �e plik istnieje na dysku");
     }

   }

}
//---------------------------------------------------------------------------

void __fastcall TForm1::Zapiszjako1Click(TObject *Sender)
{
   if (SaveDialog1->Execute())
   {
     try
     {
        Content->Lines->SaveToFile(SaveDialog1->FileName);
        File_Name = SaveDialog1->FileName;

     }

     catch (...)
     {

        ShowMessage("Zapis zako�czy� si� niepowodzeniem!");
     }

   }
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Zapisz1Click(TObject *Sender)
{
        if (File_Name!="")
        {
           Content->Lines->SaveToFile(File_Name);
        }
        else
        {
            Form1->Zapiszjako1Click(MainMenu1);
        }
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Nowy1Click(TObject *Sender)
{
    if(Application->MessageBox(
    "Czy na pewno utworzy� nowy plik?","Potwierd�",
    MB_YESNOCANCEL | MB_ICONQUESTION) == IDYES )
    {
       Content->Lines->Clear();
       File_Name="";
    }
}
//---------------------------------------------------------------------------
void __fastcall TForm1::ContentKeyDown(TObject *Sender, WORD &Key,
      TShiftState Shift)
{
     if (Shift.Contains(ssCtrl))
     {
        if ((Key == 's') || (Key == 'S'))
        {
            Form1->Zapisz1Click(MainMenu1);
        }



     }
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Zakocz1Click(TObject *Sender)
{
    if(Application->MessageBox(
    "Czy na pewno zako�czy� program?","Potwierd�",
    MB_YESNO | MB_ICONQUESTION) == IDYES )
    {
        Application->Terminate();
    }
 
}
//---------------------------------------------------------------------------
void __fastcall TForm1::FormClose(TObject *Sender, TCloseAction &Action)
{
    if(Application->MessageBox(
    "Czy na pewno zako�czy� program?","Potwierd�",
    MB_YESNO | MB_ICONQUESTION) == IDNO )
    {
        Action=caNone;
    }
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Wytnij1Click(TObject *Sender)
{
    Content->CutToClipboard();
}
//---------------------------------------------------------------------------
void __fastcall TForm1::KopiujCtrlC1Click(TObject *Sender)
{
    Content->CopyToClipboard();
}
//---------------------------------------------------------------------------
void __fastcall TForm1::WklejCtrlV1Click(TObject *Sender)
{
    Content->PasteFromClipboard();
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Zawijaniewierszy1Click(TObject *Sender)
{

   if (Zawijaniewierszy1->Checked==true)
   {
      Zawijaniewierszy1->Checked=false;
      Content->WordWrap=false;
      Content->ScrollBars = ssBoth;
   }
   else
   {
      Zawijaniewierszy1->Checked=true;
      Content->WordWrap = true;
      Content->ScrollBars = ssVertical;

   }



}
//---------------------------------------------------------------------------
void __fastcall TForm1::czcionka1Click(TObject *Sender)
{
   if (FontDialog1->Execute())
   {
     //kroj
     Content->Font->Name = FontDialog1->Font->Name;

     //kolor
     Content->Font->Color = FontDialog1->Font->Color;

     //rozmiar
     Content->Font->Size = FontDialog1->Font->Size;

     //styl
     Content->Font->Style = FontDialog1->Font->Style;


   }
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Oprogramie1Click(TObject *Sender)
{
   Form2->ShowModal();
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Zapraszamnabloga1Click(TObject *Sender)
{
   ShellExecute(NULL,"open","http://matmozaur.pl", NULL, NULL, SW_SHOWNORMAL);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Przyspieszanie1Click(TObject *Sender)
{
        GroupBox1->Visible=true;
        Faster=true;
        if(type!='o') Label1->Caption=Przyspieszanie1->Caption;

}
//---------------------------------------------------------------------------



void __fastcall TForm1::Opoznianie1Click(TObject *Sender)
{
        GroupBox1->Visible=true;
        Faster=false;
        if(type!='o') Label1->Caption=Opoznianie1->Caption;

}
//---------------------------------------------------------------------------


void __fastcall TForm1::Button1Click(TObject *Sender)
{
        GroupBox1->Visible=false;
        String  n,s,e;
        n=Edit1->Text;
        s=Edit2->Text;
        e=Edit3->Text;
        ChangeSub(Faster,File_Name,n,s,e,type);
}
//---------------------------------------------------------------------------







void __fastcall TForm1::Polski1Click(TObject *Sender)
{
            LangChange(lang,'p');
}

//---------------------------------------------------------------------------


void __fastcall TForm1::Angielski1Click(TObject *Sender)
{
            LangChange(lang,'e');
}
//---------------------------------------------------------------------------


