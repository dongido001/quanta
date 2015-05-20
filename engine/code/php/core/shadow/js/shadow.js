// Add/Edit page form.
// TODO: this has all to be refactored.

function pageEdit(action) {
    openShadow(action);
    $.getScript('/engine/code/php/core/file/js/jquery.fileupload.js');
    $.getScript('/engine/code/php/core/file/js/file-upload.js');
}

function pageDelete() {
    openShadow('node_delete');
}

function openShadow(context) {
    $('#shadow-item').html('').attr('rel', context).load('?shadow=' + context, function() {
        pageRefresh();
        refreshButtons();
        $('.shadow-title').find('a').on('click', function () {
            if (!($(this).parent().hasClass('enabled'))) {
                $('.enabled').removeClass('enabled');
                $(this).parent().addClass('enabled');
                $('#shadow-content-' + $(this).attr('rel')).addClass('enabled');
            }
            return false;
        });
    });
    $('#shadow-outside').fadeIn('slow');
}

function logIn() {
    openShadow('user_login');
}

function logOut() {
   action('{"action": "logout"}');
}

/**
 * Submit a shadow form.
 */
function shadowSubmit() {
    var form_items = {};
    $('#shadow-outside').find('input, textarea, select').each(function() {
        form_items[$(this).attr('name')] = $(this).val();
    });
    var formData = JSON.stringify(form_items);
        //$('body').html(formData);
        //return;
        action(formData);
}


