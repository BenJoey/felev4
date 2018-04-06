package body Aircraft is
   procedure Ascend(Airc: in out Aircraft_Type) is
   begin
      Airc.Is_In_The_Air := True;
   end Ascend;

   procedure Land(Airc: in out Aircraft_Type) is
   begin
      Airc.Is_In_The_Air := False;
   end Land;

   function Get_Is_In_The_Air(Airc:Aircraft_Type) return Boolean is
   begin
      return Airc.Is_In_The_Air;
   end Get_Is_In_The_Air;

   function Get_Coord(Airc:Aircraft_Type) return Coord is
   begin
      return Airc.Poz;
   end Get_Coord;

   procedure Set_Coord(Airc: in out Aircraft_Type; Val:Coord) is
   begin
      Set_X(Airc.Poz,Get_X(Val));
      Set_Y(Airc.Poz,Get_Y(Val));
   end Set_Coord;

   procedure Set_Card_Dir_Coord(Airc: in out Aircraft_Type; Val:Card_Dir.Cardinal_Direction) is
   begin
      Change_To_Direction(Airc.Poz,Val);
   end Set_Card_Dir_Coord;

   procedure Start(Airc: in out Aircraft_Type) is
      Temp : Coord;
   begin
      Set_X(Temp,RandGen.generate_random_number(20));
      Set_Y(Temp,RandGen.generate_random_number(20));
      Set_Coord(Airc,Temp);
   end Start;

   function Compare(Airc1: Aircraft_Type;Airc2: Aircraft_Type) return Boolean is
   begin
      return Airc1.Azon<Airc2.Azon;
   end Compare;

   function Get_Distance(Airc1: Aircraft_Type;Airc2: Aircraft_Type) return Integer is
   begin
      return Get_Distance(Airc1.Poz,Airc2.Poz);
   end Get_Distance;

   procedure Action(Airc: out Aircraft_Type) is
   begin
      Change_All(Airc.Azon,Airc.Poz,Airc.Is_In_The_Air);
   end Action;

end Aircraft;
