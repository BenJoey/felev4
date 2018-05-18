with Ada.Text_IO,Ada.Unchecked_Deallocation, Ada.Numerics.Float_Random;
use Ada.Text_IO, Ada.Numerics.Float_Random;

procedure Traffic_Sim is

   --------DEKLARACIOK-------------

   type Szin is (Piros, Piros_Sarga, Zold, Sarga);
   type PString is access all String;

   protected Multi_Printer is
      function Rand_Dur return Duration;
      procedure Kiir(S:in String);
   end Multi_Printer;

   protected Lamp is
      function Color return Szin;
      procedure Switch;
   private
      Lampa:Szin:=Piros;
   end Lamp;

   task Controller is
      entry Stop;
   end Controller;

   protected Crossroad is
      procedure Wake_Up;
      entry Cross(Ido:in Duration);
   end Crossroad;

   task type Vehicle(Rszam:PString);

   task type Signal;
   type PSignal is access Signal;
   procedure FREESign is new Ada.Unchecked_Deallocation(Signal,PSignal);

   ---------DEKLARACIOK VEGE---------

   protected body Multi_Printer is
      function Rand_Dur return Duration is
         G:Generator;
         F:Float;
      begin
         Reset(G);
         F:=Random(G);
         return Duration(F);
      end Rand_Dur;
      procedure Kiir(S:in String)is
      begin
         Put_Line(S);
      end Kiir;
   end Multi_Printer;

   task body Signal is
   begin
      Crossroad.Wake_Up;
   end Signal;

   protected body Lamp is
      function Color return Szin is
      begin
         return Lampa;
      end Color;
      procedure Switch is
         S:PSignal;
      begin
         if Lampa=Sarga then
            Lampa:=Piros;
         else
            Lampa:=Szin'Succ(Lampa);
         end if;
         Multi_Printer.Kiir("A lampa jelenleg: " & Lampa'Image);
         S := new Signal;
         FREESign(S);
      end Switch;
   end Lamp;

   task body Controller is
      Active:Boolean := True;
      Del:Duration:=3.0;
   begin
      while Active loop
         select
            accept Stop do
               Active := False;
            end Stop;
         else
            delay Del;
            Lamp.Switch;
            case Lamp.Color is
               when Piros => Del := 3.0;
               when Piros_Sarga => Del := 1.0;
               when Zold => Del := 3.0;
               when Sarga => Del := 2.0;
            end case;
         end select;
      end loop;
   end Controller;

   task body Vehicle is
      Cross_Time:Duration:=Multi_Printer.Rand_Dur + 0.5;
   begin
      Multi_Printer.Kiir(Rszam.all & " rendszamu auto a keresztezodeshez ert.");
      select
         Crossroad.Cross(Cross_Time);
      else
         Cross_Time:=Multi_Printer.Rand_Dur + 2.5;
         Crossroad.Cross(Cross_Time);
      end select;
      Multi_Printer.Kiir(Rszam.all & " rendszamu auto atkelt.");
   end Vehicle;

   protected body Crossroad is
      procedure Wake_Up is
      begin
         null;
      end Wake_Up;
      entry Cross(Ido: in Duration) when Lamp.Color=Zold is
      begin
         delay Ido;
      end Cross;
   end Crossroad;

   type Car_Arr is array (1..10) of access Vehicle;
   type Lic_Plates is array (1..10) of PString;

   Autok:Car_Arr;
   Rszamok:Lic_Plates:=(new String'("ADA-000"), new String'("CPP-111"), new String'("PRG-222"),new String'("MOD-333"),
                        new String'("KAT-444"),  new String'("ALO-555"), new String'("GUS-666"),
                        new String'("SZE-777"), new String'("MLE-888"), new String'("LET-999"));
begin
   for I in Autok'Range loop
      Autok(I) := new Vehicle(Rszamok(I));
      delay 0.5;
   end loop;
   --delay 10.0;
   loop
      if Autok(Autok'Last).all'Terminated then  --Mivel erkezesi sorrendben jonnek az autok igy elég megnezni, hogy az utolso atkelt-e
         exit;
      end if;
   end loop;
   Controller.Stop;
end Traffic_Sim;
