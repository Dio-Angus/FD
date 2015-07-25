<GameProjectFile>
  <PropertyGroup Type="Scene" Name="EditScene" ID="2c573592-7ebf-45f7-adeb-d51a344eae3d" Version="2.0.6.0" />
  <Content ctype="GameProjectContent">
    <Content>
      <Animation Duration="0" Speed="1.0000" />
      <ObjectData Name="Scene" FrameEvent="" Tag="17" ctype="SingleNodeObjectData">
        <Position X="0.0000" Y="0.0000" />
        <Scale ScaleX="1.0000" ScaleY="1.0000" />
        <AnchorPoint />
        <CColor A="255" R="255" G="255" B="255" />
        <Size X="480.0000" Y="800.0000" />
        <PrePosition X="0.0000" Y="0.0000" />
        <PreSize X="0.0000" Y="0.0000" />
        <Children>
          <NodeObjectData Name="backGround0" ActionTag="-826556048" FrameEvent="" Tag="18" ObjectIndex="1" ctype="SpriteObjectData">
            <Position X="239.9999" Y="398.5714" />
            <Scale ScaleX="1.0000" ScaleY="1.0000" />
            <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
            <CColor A="255" R="255" G="255" B="255" />
            <Size X="480.0000" Y="800.0000" />
            <PrePosition X="0.5000" Y="0.4982" />
            <PreSize X="0.0000" Y="0.0000" />
            <FileData Type="Normal" Path="backGround0.jpg" />
          </NodeObjectData>
          <NodeObjectData Name="playLayer" ActionTag="-213987583" Alpha="127" FrameEvent="" Tag="22" ObjectIndex="2" ctype="SpriteObjectData">
            <Position X="240.0000" Y="400.0000" />
            <Scale ScaleX="1.0000" ScaleY="1.0000" />
            <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
            <CColor A="255" R="255" G="255" B="255" />
            <Size X="400.0000" Y="600.0000" />
            <PrePosition X="0.5000" Y="0.5000" />
            <PreSize X="0.0000" Y="0.0000" />
            <FileData Type="Normal" Path="playLayer.jpg" />
          </NodeObjectData>
          <NodeObjectData Name="backBtn" ActionTag="1715468680" FrameEvent="" Tag="23" ObjectIndex="1" TouchEnable="True" FontSize="36" ButtonText="返回" Scale9Width="120" Scale9Height="50" ctype="ButtonObjectData">
            <Position X="100.0000" Y="50.0000" />
            <Scale ScaleX="1.0000" ScaleY="1.0000" />
            <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
            <CColor A="255" R="255" G="255" B="255" />
            <Size X="120.0000" Y="50.0000" />
            <PrePosition X="0.2083" Y="0.0625" />
            <PreSize X="0.0000" Y="0.0000" />
            <FontResource Type="Normal" Path="0.ttf" />
            <TextColor A="255" R="0" G="0" B="254" />
            <DisabledFileData Type="Default" Path="Default/Button_Disable.png" />
            <PressedFileData Type="Normal" Path="Button1.jpg" />
            <NormalFileData Type="Normal" Path="Button1.jpg" />
          </NodeObjectData>
          <NodeObjectData Name="doneBtn" ActionTag="-1806818076" FrameEvent="" Tag="25" ObjectIndex="2" TouchEnable="True" FontSize="36" ButtonText="完成" Scale9Width="120" Scale9Height="50" ctype="ButtonObjectData">
            <Position X="380.0000" Y="50.0000" />
            <Scale ScaleX="1.0000" ScaleY="1.0000" />
            <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
            <CColor A="255" R="255" G="255" B="255" />
            <Size X="120.0000" Y="50.0000" />
            <PrePosition X="0.7917" Y="0.0625" />
            <PreSize X="0.0000" Y="0.0000" />
            <FontResource Type="Normal" Path="0.ttf" />
            <TextColor A="255" R="0" G="0" B="254" />
            <DisabledFileData Type="Default" Path="Default/Button_Disable.png" />
            <PressedFileData Type="Normal" Path="Button1.jpg" />
            <NormalFileData Type="Normal" Path="Button1.jpg" />
          </NodeObjectData>
          <NodeObjectData Name="ScoreGround" ActionTag="86530639" FrameEvent="" Tag="26" ObjectIndex="4" ctype="SpriteObjectData">
            <Position X="183.3000" Y="745.0000" />
            <Scale ScaleX="1.1139" ScaleY="1.1237" />
            <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
            <CColor A="255" R="255" G="255" B="255" />
            <Size X="256.0000" Y="256.0000" />
            <PrePosition X="0.3819" Y="0.9312" />
            <PreSize X="0.0000" Y="0.0000" />
            <FileData Type="Normal" Path="Button.png" />
          </NodeObjectData>
          <NodeObjectData Name="MoveGround" ActionTag="-945399940" FrameEvent="" Tag="27" ObjectIndex="5" ctype="SpriteObjectData">
            <Position X="398.1300" Y="750.0000" />
            <Scale ScaleX="0.3424" ScaleY="1.1237" />
            <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
            <CColor A="255" R="255" G="255" B="255" />
            <Size X="256.0000" Y="256.0000" />
            <PrePosition X="0.8294" Y="0.9375" />
            <PreSize X="0.0000" Y="0.0000" />
            <FileData Type="Normal" Path="Button.png" />
          </NodeObjectData>
          <NodeObjectData Name="ScoreText" ActionTag="-742963645" FrameEvent="" Tag="28" ObjectIndex="1" FontSize="36" LabelText="Score:" ctype="TextObjectData">
            <Position X="96.8986" Y="746.5300" />
            <Scale ScaleX="0.6464" ScaleY="1.0000" />
            <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
            <CColor A="255" R="21" G="95" B="15" />
            <Size X="99.0000" Y="39.0000" />
            <PrePosition X="0.2019" Y="0.9332" />
            <PreSize X="0.0000" Y="0.0000" />
            <FontResource Type="Normal" Path="1.ttf" />
          </NodeObjectData>
          <NodeObjectData Name="Score" ActionTag="853090423" FrameEvent="" Tag="29" ObjectIndex="1" TouchEnable="True" FontSize="48" IsCustomSize="True" LabelText="" PlaceHolderText="0" MaxLengthEnable="True" MaxLengthText="9" ctype="TextFieldObjectData">
            <Position X="218.3300" Y="748.8200" />
            <Scale ScaleX="0.6000" ScaleY="1.0000" />
            <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
            <CColor A="255" R="18" G="19" B="255" />
            <Size X="249.0000" Y="52.0000" />
            <PrePosition X="0.4549" Y="0.9360" />
            <PreSize X="0.5188" Y="0.0650" />
            <FontResource Type="Normal" Path="1.ttf" />
          </NodeObjectData>
          <NodeObjectData Name="Step" ActionTag="257248434" FrameEvent="" Tag="30" ObjectIndex="2" TouchEnable="True" FontSize="36" IsCustomSize="True" LabelText="" PlaceHolderText="0" MaxLengthEnable="True" MaxLengthText="2" ctype="TextFieldObjectData">
            <Position X="398.1300" Y="750.0000" />
            <Scale ScaleX="1.5391" ScaleY="1.4000" />
            <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
            <CColor A="255" R="0" G="24" B="255" />
            <Size X="42.0000" Y="39.0000" />
            <PrePosition X="0.8294" Y="0.9375" />
            <PreSize X="0.0875" Y="0.0487" />
            <FontResource Type="Normal" Path="1.ttf" />
          </NodeObjectData>
        </Children>
      </ObjectData>
    </Content>
  </Content>
</GameProjectFile>