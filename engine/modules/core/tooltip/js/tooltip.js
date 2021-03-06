$(document).ready(function () {
  $('body').append('<div id="tooltip"></div>');
});

$(document).bind('refresh', function () {
  var dataTooltip = $("body").find("[data-tooltip]:not(empty)");
  // Create a mouseover effect to display tooltips.
	dataTooltip.on('mouseover', function () {
  var tooltip = $('#tooltip');
		// Generate the tooltip's html.
    tooltip.html(quanta_html_escape($(this).data('tooltip'))).show();
    tooltip.css('color', $(this).css('color'));
    $(document).off('mousemove').on('mousemove', function (e) {
      var tipLeft = (e.pageX > ($(window).width() / 2)) ? (e.pageX - tooltip.innerWidth()) : (e.pageX + 10);
      var tipTop = (e.pageY > ($(window).height() / 2)) ? (e.pageY - tooltip.innerHeight()) : (e.pageY + 10);
      tooltip.css({
        left: tipLeft,
        top: tipTop
      });
    });
  });
  dataTooltip.on('mouseout', function () {
  var tooltip = $('#tooltip');
    tooltip.unbind();
    tooltip.hide();
  });
});
