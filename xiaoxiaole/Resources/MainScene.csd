<GameProjectFile>
  <PropertyGroup Type="Scene" Name="MainScene" ID="1bd59cc4-da3b-4131-9b35-48bc0b637b58" Version="2.0.6.0" />
  <Content ctype="GameProjectContent">
    <Content>
      <Animation Duration="0" Speed="1.0000" />
      <ObjectData Name="Scene" FrameEvent="" ctype="SingleNodeObjectData">
        <Position X="0.0000" Y="0.0000" />
        <Scale ScaleX="1.0000" ScaleY="1.0000" />
        <AnchorPoint />
        <CColor A="255" R="255" G="255" B="255" />
        <Size X="480.0000" Y="800.0000" />
        <PrePosition X="0.0000" Y="0.0000" />
        <PreSize X="0.0000" Y="0.0000" />
        <Children>
          <NodeObjectData Name="backGround" ActionTag="-1805429380" FrameEvent="" Tag="3" ObjectIndex="1" ctype="SpriteObjectData">
            <Position X="240.0000" Y="400.0000" />
            <Scale ScaleX="1.0000" ScaleY="1.0000" />
            <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
            <CColor A="255" R="255" G="255" B="255" />
            <Size X="480.0000" Y="800.0000" />
            <PrePosition X="0.5000" Y="0.5000" />
            <PreSize X="0.0000" Y="0.0000" />
            <FileData Type="Normal" Path="backGround0.jpg" />
          </NodeObjectData>
          <NodeObjectData Name="PlayGround" ActionTag="440268780" Alpha="127" FrameEvent="" Tag="4" ObjectIndex="2" ctype="SpriteObjectData">
            <Position X="240.0000" Y="400.0000" />
            <Scale ScaleX="1.0000" ScaleY="1.0000" />
            <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
            <CColor A="255" R="255" G="255" B="255" />
            <Size X="400.0000" Y="600.0000" />
            <PrePosition X="0.5000" Y="0.5000" />
            <PreSize X="0.0000" Y="0.0000" />
            <FileData Type="Normal" Path="playLayer.jpg" />
          </NodeObjectData>
          <NodeObjectData Name="Congratulations" ActionTag="-1036748927" VisibleForFrame="False" FrameEvent="" Tag="5" ObjectIndex="1" FontSize="48" LabelText="Goal done!" ctype="TextObjectData">
            <Position X="322.0001" Y="48.0000" />
            <Scale ScaleX="1.2000" ScaleY="1.3000" />
            <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
            <CColor A="255" R="255" G="0" B="0" />
            <Size X="235.0000" Y="52.0000" />
            <PrePosition X="0.6708" Y="0.0600" />
            <PreSize X="0.0000" Y="0.0000" />
            <FontResource Type="Normal" Path="1.ttf" />
          </NodeObjectData>
          <NodeObjectData Name="Fail" ActionTag="-782960520" VisibleForFrame="False" FrameEvent="" Tag="16" ObjectIndex="5" FontSize="48" LabelText="You failed!" ctype="TextObjectData">
            <Position X="316.0002" Y="48.0002" />
            <Scale ScaleX="1.2000" ScaleY="1.3000" />
            <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
            <CColor A="255" R="144" G="0" B="32" />
            <Size X="248.0000" Y="52.0000" />
            <PrePosition X="0.6583" Y="0.0600" />
            <PreSize X="0.0000" Y="0.0000" />
            <FontResource Type="Normal" Path="1.ttf" />
          </NodeObjectData>
          <NodeObjectData Name="MoveGround" ActionTag="20474814" FrameEvent="" Tag="6" ObjectIndex="3" ctype="SpriteObjectData">
            <Position X="398.3000" Y="745.1600" />
            <Scale ScaleX="0.3424" ScaleY="1.1237" />
            <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
            <CColor A="255" R="255" G="255" B="255" />
            <Size X="256.0000" Y="256.0000" />
            <PrePosition X="0.8298" Y="0.9314" />
            <PreSize X="0.0000" Y="0.0000" />
            <FileData Type="Normal" Path="Button.png" />
          </NodeObjectData>
          <NodeObjectData Name="Step" ActionTag="-579560808" FrameEvent="" Tag="7" ObjectIndex="2" FontSize="36" LabelText="48" ctype="TextObjectData">
            <Position X="398.1300" Y="750.0000" />
            <Scale ScaleX="1.5391" ScaleY="1.4000" />
            <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
            <CColor A="255" R="0" G="24" B="255" />
            <Size X="42.0000" Y="39.0000" />
            <PrePosition X="0.8294" Y="0.9375" />
            <PreSize X="0.0000" Y="0.0000" />
            <FontResource Type="Normal" Path="1.ttf" />
          </NodeObjectData>
          <NodeObjectData Name="ScoreGround" ActionTag="375276463" FrameEvent="" Tag="8" ObjectIndex="4" ctype="SpriteObjectData">
            <Position X="183.3000" Y="745.0000" />
            <Scale ScaleX="1.1139" ScaleY="1.1237" />
            <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
            <CColor A="255" R="255" G="255" B="255" />
            <Size X="256.0000" Y="256.0000" />
            <PrePosition X="0.3819" Y="0.9312" />
            <PreSize X="0.0000" Y="0.0000" />
            <FileData Type="Normal" Path="Button.png" />
          </NodeObjectData>
          <NodeObjectData Name="ScoreText" ActionTag="856671192" FrameEvent="" Tag="9" ObjectIndex="3" FontSize="36" LabelText="Score:" ctype="TextObjectData">
            <Position X="95.4700" Y="746.5300" />
            <Scale ScaleX="0.6464" ScaleY="1.0000" />
            <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
            <CColor A="255" R="21" G="95" B="15" />
            <Size X="99.0000" Y="39.0000" />
            <PrePosition X="0.1989" Y="0.9332" />
            <PreSize X="0.0000" Y="0.0000" />
            <FontResource Type="Normal" Path="1.ttf" />
          </NodeObjectData>
          <NodeObjectData Name="Score" ActionTag="-722290938" FrameEvent="" Tag="10" ObjectIndex="4" FontSize="48" LabelText="123456798" ctype="TextObjectData">
            <Position X="218.3300" Y="748.8200" />
            <Scale ScaleX="0.6000" ScaleY="1.0000" />
            <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
            <CColor A="255" R="18" G="19" B="255" />
            <Size X="249.0000" Y="52.0000" />
            <PrePosition X="0.4549" Y="0.9360" />
            <PreSize X="0.0000" Y="0.0000" />
            <FontResource Type="Normal" Path="1.ttf" />
          </NodeObjectData>
          <NodeObjectData Name="backBtn" ActionTag="-964084736" FrameEvent="" Tag="11" ObjectIndex="1" TouchEnable="True" FontSize="36" ButtonText="返回" Scale9Width="120" Scale9Height="50" ctype="ButtonObjectData">
            <Position X="104.2855" Y="54.2857" />
            <Scale ScaleX="1.0000" ScaleY="1.0000" />
            <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
            <CColor A="255" R="255" G="255" B="255" />
            <Size X="120.0000" Y="50.0000" />
            <PrePosition X="0.2173" Y="0.0679" />
            <PreSize X="0.0000" Y="0.0000" />
            <FontResource Type="Normal" Path="0.ttf" />
            <TextColor A="255" R="0" G="0" B="254" />
            <DisabledFileData Type="Default" Path="Default/Button_Disable.png" />
            <PressedFileData Type="Normal" Path="Button1.jpg" />
            <NormalFileData Type="Normal" Path="Button1.jpg" />
          </NodeObjectData>
        </Children>
      </ObjectData>
    </Content>
  </Content>
</GameProjectFile>