with Coords,Card_Dir,RandGen;
use Coords;
generic
   type Id is (<>);
   with function "<"(A,B: Id) return Boolean is <>;
package Aircraft is
   type Aircraft_Type(Name:Id) is private;

   procedure Ascend(Airc:in out Aircraft_Type);
   procedure Land(Airc:in out Aircraft_Type);
   function Get_Is_In_The_Air(Airc:Aircraft_Type) return Boolean;
   function Get_Coord(Airc:Aircraft_Type) return Coord;
   procedure Set_Card_Dir_Coord(Airc: in out Aircraft_Type; Val:Card_Dir.Cardinal_Direction);
   procedure Start(Airc: in out Aircraft_Type);
   function Compare(Airc1: Aircraft_Type;Airc2: Aircraft_Type) return Boolean;
   function Get_Distance(Airc1: Aircraft_Type;Airc2: Aircraft_Type) return Integer;

   generic
      with procedure Change_All(Azon: out Id; Pozicio: out Coord;Air: out Boolean);
      procedure Action(Airc: out Aircraft_Type);

private
   type Aircraft_Type(Name:Id) is record
      Azon:Id:=Name;
      Poz:Coord;
      Is_In_The_Air:Boolean:=False;
   end record;

   procedure Set_Coord(Airc: in out Aircraft_Type; Val:Coord);
end Aircraft;
