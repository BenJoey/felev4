output = File.open("newdata","w")
datas = Hash.new
file = File.open("data").each do |line|
    line2 = line.split('.')
    adatok = line2[1].split(/\s*;\s*/)
    datas[line2[0].to_i] = adatok
end
file = File.open("update").each do |line|
    line2 = line.split('.')
    if datas[line2[0].to_i].nil?
        adatok = line2[1].split(/\s*;\s*/)
        datas[line2[0].to_i] = adatok
    elsif line2[1].strip=="visszavon"
        datas.delete(line2[0].to_i)
    else
        datas[line2[0].to_i][2]=line2[1].strip
    end
end
datas.sort.to_h.each do |key,value|
    output.puts String(key) +". "+value[0].strip+"; "+value[1]+"; "+value[2]
end