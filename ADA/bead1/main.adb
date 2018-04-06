with Ada.Text_IO, Aircraft, Coords, Card_Dir;
use Coords;
procedure Main is
   --Aircraft csomag tesztjei
   function TestAircraft return Boolean is
      function Asc(A,B : in Integer) return Boolean is (A > B);
      function Desc(A,B : in Integer) return Boolean is (A < B);
      type Egtajak is array (1..8) of Card_Dir.Cardinal_Direction;

      procedure Nullazas(Azon: out Integer; Koord: out Coord; Repul: out Boolean) is
      begin
         Azon := 0000;
         Set_X(Koord,0);
         Set_Y(Koord,0);
         Repul := False;
      end Nullazas;

      --Kulonbozo osszehasonlitasos csomagok
      package Repulok1 is new Aircraft(Integer,Asc);
      package Repulok2 is new Aircraft(Integer,Desc);

      --Action fuggveny deklaracio
      procedure KivonForgalom is new Repulok1.Action(Nullazas);

      Airc_1 : Repulok1.Aircraft_Type(3672);
      Airc_2 : Repulok1.Aircraft_Type(2674);
      Airc_3 : Repulok2.Aircraft_Type(6913);
      Airc_4 : Repulok2.Aircraft_Type(8163);
      seged : Coord;
      x,y : Integer;
      iranyok : Egtajak := (Card_Dir.N, Card_Dir.NE, Card_Dir.E, Card_Dir.SE, Card_Dir.S, Card_Dir.SW, Card_Dir.W, Card_Dir.NW);
   begin
      Repulok1.Start(Airc_1);
      Repulok1.Start(Airc_2);
      Repulok2.Start(Airc_3);
      Repulok2.Start(Airc_4);

      --Repul-e fuggveny teszt
      Repulok1.Ascend(Airc_1);
      Repulok2.Ascend(Airc_4);
      if not (Repulok1.Get_Is_In_The_Air(Airc_1) and Repulok2.Get_Is_In_The_Air(Airc_4)) then
         return false;
      end if;

      --Repulo mozgasanak tesztje
      for I in iranyok'Range loop
         x := 0 ;y := 0;
         seged := Repulok1.Get_Coord(Airc_1);
         Repulok1.Set_Card_Dir_Coord(Airc_1,iranyok(I));
         case iranyok(I) is
            when Card_Dir.N => y := -1;
            when Card_Dir.S => y := 1;
            when Card_Dir.E => x := 1;
            when Card_Dir.W => x := -1;
            when Card_Dir.NE => x := 1;y := -1;
            when Card_Dir.SE => x := 1;y := 1;
            when Card_Dir.NW => x := -1;y := -1;
            when Card_Dir.SW => x := -1;y := 1;
         end case;
         if(Get_X(seged)+x/=Get_X(Repulok1.Get_Coord(Airc_1)) or Get_Y(seged)+y/=Get_Y(Repulok1.Get_Coord(Airc_1))) then
            return False;
         end if;
      end loop;

      --Compare fuggveny teszt
      if not (Repulok1.Compare(Airc_1,Airc_2) and Repulok2.Compare(Airc_3,Airc_4)) then
         return False;
      end if;

      --GetDistance fuggveny teszt
      if not (Repulok1.Get_Distance(Airc_1,Airc_2)=Repulok1.Get_Distance(Airc_2,Airc_1)) then
         return False;
      end if;

      --Action fuggveny teszt
      KivonForgalom(Airc_2);
      Set_X(seged,0);
      Set_Y(seged,0);
      if (Repulok1.Get_Is_In_The_Air(Airc_2) or Get_Distance(seged, Repulok1.Get_Coord(Airc_2))/=0) then
         return False;
      end if;

      return True;
   end TestAircraft;

   --Coords csomag tesztjei
   function TestCoords return Boolean is
      type TestMatrix is array (Integer range <>, Integer range <>) of Integer;
      TestM : TestMatrix(1..10,1..10);
      Test1,Test2 : Coord;

      --Matrix feltoltese
      procedure MatrFeltolt (T : in out TestMatrix) is
      begin
         for I in T'Range(1) loop
            for J in T'Range(2) loop
               T(I,J) := (I-1)*10+J; -- A matrixban 1-tol 100-ig elhelyezzuk a szamokat
            end loop;
         end loop;
      end MatrFeltolt;

      function CoordArrayTest is new Coord_With_Array(Integer,TestMatrix);

   begin
      --Setter es Getter tesztek
      Set_X(Test1,3);
      Set_Y(Test1,7);
      if (Get_X(Test1)/=3 or Get_Y(Test1)/=7) then
         return False;
      end if;

      --GetDistance fuggveny teszt
      Set_X(Test2,6);
      Set_Y(Test2,2);
      if Get_Distance(Test1,Test2)/=34 then --(3-6)^2+(7-2)^2=34
         return False;
      end if;

      --Coord_With_Array fuggveny teszt
      MatrFeltolt(TestM);
      if not (CoordArrayTest(Test1,TestM)=27 and CoordArrayTest(Test2,TestM)=52) then
         return False;
      end if;

      --Change_To_Direction fuggveny tesztelese mar szerepel az Aircraft csomag tesztjei kozott
      return True;
   end TestCoords;

begin
   if not (TestAircraft and TestCoords) then
        Ada.Text_IO.Put_Line("Tests Failed :( ");
   else
        Ada.Text_IO.Put_Line("Tests Passed :) ");
   end if;
end Main;
