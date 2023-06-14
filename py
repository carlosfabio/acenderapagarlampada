from tkinter import*
import webbrowser
janela = Tk()
janela.title("LUZ - ACENDER/APAGAR")
# janela.geometry('320x110')

def ola():
     new=0
     url="http://192.168.0.110/facacomarduino/LampadaOn"

     webbrowser.open(url,new=new)
 
botao = Button(janela, text = "Acender", background='green',  font = ("Helvetica", 25),  command = ola )
botao.grid(column=0, row=0)


def ola2():
     new=0
     url="http://192.168.0.110/facacomarduino/LampadaOff"

     webbrowser.open(url,new=new)

botao = Button(janela, text = "Apagar", background='yellow', font = ("Helvetica", 25),  command = ola2 )
botao.grid(column=60, row=0)
janela.mainloop()
